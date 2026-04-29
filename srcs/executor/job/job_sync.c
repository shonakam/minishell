#include "../executor_internal.h"

static bool	update_process_status(t_context *ctx, t_job *job, size_t i)
{
	int		status;
	pid_t	res;

	res = waitpid(job->pids[i], &status, WNOHANG);
	if (res == 0)
		return (true);
	if (res == job->pids[i] || (res == -1 && errno == ECHILD))
	{
		if (res == job->pids[i] && i == job->count - 1)
		{
			if (WIFEXITED(status))
				ctx->last_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				ctx->last_status = STATUS_SIGNAL_INTERRUPT + WTERMSIG(status);
		}
		job->pids[i] = 0;
	}
	return (false);
}

static bool	is_job_completed(t_context *ctx, t_job *job)
{
	size_t	i;
	bool	still_running;

	if (!job || !job->pids || job->count == 0)
		return (true);
	still_running = false;
	i = 0;
	while (i < job->count)
	{
		if (job->pids[i] > 0)
		{
			if (update_process_status(ctx, job, i))
				still_running = true;
		}
		i++;
	}
	return (!still_running);
}

static void	print_job_status(t_context *ctx, t_job *job)
{
	char	mark;
	char	*cmd;

	mark = ' ';
	if (job == ctx->job.current)
		mark = '+';
	else if (job == ctx->job.previous)
		mark = '-';
	cmd = job->cmd_line;
	if (cmd == NULL)
		cmd = "";
	printf("[%zd]%c Done\t\t%s\r\n", job->job_id, mark, cmd);
}

void	job_sync(t_context *ctx)
{
	t_job	*curr;
	t_job	*next;

	curr = ctx->job.all;
	while (curr)
	{
		next = curr->next;
		if (is_job_completed(ctx, curr))
		{
			print_job_status(ctx, curr);
			job_discard(ctx, curr);
		}
		curr = next;
	}
}
