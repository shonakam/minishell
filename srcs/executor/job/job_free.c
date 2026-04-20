#include "../executor_internal.h"

void	job_free(t_job *job)
{
	if (!job)
		return ;
	if (job->cmd_line)
		free(job->cmd_line);
	if (job->pids)
		free(job->pids);
	free(job);
}
