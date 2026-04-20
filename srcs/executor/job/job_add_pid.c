#include "../executor_internal.h"

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
