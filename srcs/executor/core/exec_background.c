#include "../executor_internal.h"

static void	clean_job_for_bg(t_context *ctx)
{
	t_job	*next;
	t_job	*curr;

	curr = ctx->job.all;
	while (curr)
	{
		next = curr->next;
		job_free(curr);
		curr = next;
	}
	ctx->job.all = NULL;
	ctx->job.current = NULL;
	ctx->job.previous = NULL;
	ctx->job.fg = NULL;
	ft_history_destroy();
}

static void	bg_subroutine(t_context *ctx, t_ast_node *node)
{
	int		fd_null;

	signal_set_mode(SIG_MODE_BACKGROUND);
	clean_job_for_bg(ctx);
	fd_null = open(PATH_DEV_NULL, O_RDONLY);
	if (fd_null != -1)
	{
		x_dup2(fd_null, STDIN_FILENO);
		close(fd_null);
	}
	exec_engine(ctx, node->left);
	safe_exit(ctx, NULL, NULL, ctx->last_status);
}

void	exec_background(t_context *ctx, t_ast_node *node)
{
	pid_t	pid;
	t_job	*job;
	char	*cmd_line;

	if (!node || !node->left)
		return ;
	cmd_line = ast_to_str(node->left);
	job = job_new(get_next_job_id(ctx), cmd_line, true);
	free(cmd_line);
	if (!job)
		return ;
	if (!x_fork(&pid))
		return ((void)job_free(job));
	if (pid == 0)
	{
		job_free(job);
		bg_subroutine(ctx, node);
	}
	job_add_pid(job, pid);
	job_register(ctx, job);
	signal_set_mode(SIG_MODE_IDLE);
}
