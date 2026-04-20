#include "../executor_internal.h"

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
