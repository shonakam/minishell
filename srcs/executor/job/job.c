#include "../executor_internal.h"

t_job	*job_new(ssize_t id, char *cmd_line, bool is_background)
{
	t_job	*job;

	job = x_calloc(1, sizeof(t_job));
	if (!job)
		return (NULL);
	job->job_id = id;
	job->cmd_line = x_strdup(cmd_line);
	if (!job->cmd_line)
		return (free(job), NULL);
	job->is_background = is_background;
	job->capacity = _POSIX_CHILD_MAX;
	job->pids = x_calloc(job->capacity, sizeof(pid_t));
	if (!job->pids)
		return (free(job->cmd_line), free(job), NULL);
	return (job);
}

void	job_free(t_job *job)
{
	if (!job)
		return ;
	free(job->cmd_line);
	free(job->pids);
	free(job);
}
