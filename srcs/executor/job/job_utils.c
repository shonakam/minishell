#include "../executor_internal.h"

ssize_t	get_next_job_id(t_context *ctx)
{
	ssize_t	id;
	t_job	*curr;

	id = 1;
	while (true)
	{
		curr = ctx->job.all;
		while (curr)
		{
			if (curr->job_id == id)
				break ;
			curr = curr->next;
		}
		if (curr == NULL)
			return (id);
		id++;
	}
}

bool	job_add_pid(t_job *job, pid_t pid)
{
	pid_t	*new_pids;
	size_t	new_cap;

	if (!job)
		return (false);
	if (job->count >= job->capacity)
	{
		new_cap = job->capacity * 2;
		new_pids = x_realloc(
			job->pids,
			job->capacity * sizeof(pid_t),
			new_cap * sizeof(pid_t)
		);
		if (!new_pids)
			return (false);
		job->pids = new_pids;
		job->capacity = new_cap;
	}
	job->pids[job->count++] = pid;
	return (true);
}

bool	job_is_finished(t_job *job)
{
	size_t	i;
	int		status;
	pid_t	res;

	if (!job || job->count == 0)
		return (true);
	i = 0;
	while (i < job->count)
	{
		res = waitpid(job->pids[i], &status, WNOHANG);
		if (res == 0)
			return (false);
		i++;
	}
	return (true);
}
