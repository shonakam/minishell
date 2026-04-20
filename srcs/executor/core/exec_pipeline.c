#include "../executor_internal.h"

static void	add_node_to_list(
	t_ast_node ***cmds, int *count, t_ast_node *new_node)
{
	*cmds = x_realloc(*cmds,
		sizeof(t_ast_node *) * (*count),
		sizeof(t_ast_node *) * (*count + 2));
	if (!*cmds)
		return ((void)ft_dprintf(STDERR_FILENO, ERR_MALLOC));
	(*cmds)[*count] = new_node;
	(*count)++;
	(*cmds)[*count] = NULL;
}

static void flatten_pipeline(t_ast_node *node, t_ast_node ***cmds, int *count)
{
	if (node->type == NODE_PIPELINE)
	{
		flatten_pipeline(node->left, cmds, count);
		flatten_pipeline(node->right, cmds, count);
	}
	else
		add_node_to_list(cmds, count, node);
}

static void	prepare_pipe_sub(int pr_fd, int p[2], bool has_next)
{
	if (pr_fd != -1)
	{
		x_dup2(pr_fd, STDIN_FILENO);
		close(pr_fd);
	}
	if (has_next)
	{
		close(p[0]);
		x_dup2(p[1], STDOUT_FILENO);
		close(p[1]);
	}
}

static void	pipeline_loop(t_context *ctx, t_ast_node **cmds, int n)
{
	t_pipeline_manager	pm;

	pm.i = 0;
	pm.pr_fd = -1;
	while (pm.i < n)
	{
		if (pm.i < n - 1 && !x_pipe(pm.p))
			break ;
		if (x_fork(&pm.pid) && pm.pid == 0)
		{
			prepare_pipe_sub(pm.pr_fd, pm.p, pm.i < n - 1);
			oneshot(ctx, cmds[pm.i]);
		}
		if (pm.pr_fd != -1)
			close(pm.pr_fd);
		pm.pr_fd = -1;
		if (pm.i < n - 1)
		{
			close(pm.p[1]);
			pm.pr_fd = pm.p[0];
		}
		job_add_pid(ctx->job.current, pm.pid);
		pm.i++;
	}
}

void	exec_pipeline(t_context *ctx, t_ast_node *node)
{
	t_ast_node	**cmds;
	int			n;
	char		*cmd_line;

	n = 0;
	cmds = NULL;
	flatten_pipeline(node, &cmds, &n);
	if (!cmds)
		return ;
	cmd_line = ast_to_str(node);
	ctx->job.current = job_create(ctx, cmd_line, false);
	free(cmd_line);

	signal_set_mode(SIG_MODE_EXEC);
	ctx->in_pipeline = true;
	pipeline_loop(ctx, cmds, n);
	job_wait(ctx, ctx->job.current);
	signal_set_mode(SIG_MODE_IDLE);

	ctx->job.current = NULL;
	ctx->in_pipeline = false;
}
