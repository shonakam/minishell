#include "../executor_internal.h"

static void	bg_subroutine(t_context *ctx, t_ast_node *node)
{
	int	fd_null;

	signal_set_mode(SIG_MODE_BACKGROUND);
	fd_null = open(PATH_DEV_NULL, O_RDONLY);
	if (fd_null != -1)
	{
		x_dup2(fd_null, STDIN_FILENO);
		close(fd_null);
	}
	ctx->is_subshell = true;
	exec_engine(ctx, node->left);
	exit(ctx->last_status);
}

void	exec_background(t_context *ctx, t_ast_node *node)
{
	pid_t	pid;
	t_job	*job;
	char	*cmd_line;

	if (!node || !node->left)
		return ;
	cmd_line = ast_to_str(node->left);
	job = job_create(ctx, cmd_line, true);
	if (!job)
		return ;
	if (!x_fork(&pid))
		return ((void)job_free(job));
	if (pid == 0)
	{
		bg_subroutine(ctx, node);
	}
	job->pids[0] = pid;
	job->count = 1;
	job->next = ctx->job.head;
	ctx->job.head = job;
	printf("[%zd] %d\n", job->job_id, pid);
	signal_set_mode(SIG_MODE_IDLE);
}
