#include "../executor_internal.h"

static void	update_last_status(t_context *ctx, int status)
{
	if (WIFEXITED(status))
		ctx->last_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		ctx->last_status = STATUS_SIGNAL_INTERRUPT + WTERMSIG(status);
}

static void	handle_single_process(
	t_context *ctx, t_job *job, pid_t pid, int status)
{
	signal_check_child(job->cmd_line, status);
	if (pid == job->pids[job->count - 1])
		update_last_status(ctx, status);
}

static void wait_foreground_job(t_context *ctx, t_job *job)
{
	int		status;
	size_t  i;

	i = 0;
	while (i < job->count)
	{
		if (waitpid(job->pids[i], &status, 0) > 0)
			handle_single_process(ctx, job, job->pids[i++], status);
		else
		{
			if (errno == EINTR)
				continue ;
			break ;
		}
	}
}

static void	wait_background_job(t_context *ctx, t_job *job)
{
	printf("[%zd] %d\n", job->job_id, job->pids[job->count - 1]);
	ctx->last_status = EXIT_SUCCESS;
}

void	job_wait(t_context *ctx, t_job *job)
{
	if (!job || job->count == 0)
		return ;
	if (job->is_background)
		wait_background_job(ctx, job);
	else
		wait_foreground_job(ctx, job);
}
