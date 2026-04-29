#include "../executor_internal.h"

void	pipeline_connect_io(t_context *ctx)
{
	int	io[2];

	io[0] = ctx->scope.fd_stdio[0];
	io[1] = ctx->scope.fd_stdio[1];
	if (io[0] > STDERR_FILENO)
		x_dup2(io[0], STDIN_FILENO);
	if (io[1] > STDERR_FILENO)
		x_dup2(io[1], STDOUT_FILENO);
	if (io[0] > STDERR_FILENO)
	{
		close(io[0]);
		ctx->scope.fd_stdio[0] = -1;
	}
	if (io[1] > STDERR_FILENO && io[1] != io[0])
	{
		close(io[1]);
		ctx->scope.fd_stdio[1] = STDOUT_FILENO;
	}
	else if (io[1] == io[0])
		ctx->scope.fd_stdio[1] = -1;
}

void	flatten_pipeline(t_ast_node *node, t_ast_node ***cmds, int *count)
{
	if (node->type == NODE_PIPELINE)
	{
		flatten_pipeline(node->left, cmds, count);
		flatten_pipeline(node->right, cmds, count);
		return ;
	}
	*cmds = x_realloc(*cmds, sizeof(t_ast_node *) * (*count),
			sizeof(t_ast_node *) * (*count + 2));
	if (!*cmds)
	{
		ft_dprintf(STDERR_FILENO, ERR_MALLOC);
		return ;
	}
	(*cmds)[*count] = node;
	(*count)++;
	(*cmds)[*count] = NULL;
}

void	prepare_pipe_fds(t_context *ctx, t_pipeline_manager *pm, int o, int n)
{
	ctx->scope.fd_stdio[0] = pm->pr_fd;
	ctx->scope.fd_stdio[1] = o;
	if (pm->i < n - 1)
		ctx->scope.fd_stdio[1] = pm->p[1];
}

void	update_pipe_state(t_context *ctx, t_pipeline_manager *pm, int i, int n)
{
	if (i > 0 && pm->pr_fd > STDERR_FILENO)
		close(pm->pr_fd);
	if (i < n - 1)
	{
		close(pm->p[1]);
		pm->pr_fd = pm->p[0];
	}
	else
		pm->pr_fd = -1;
	job_add_pid(ctx->job.current, pm->pid);
}
