#include "../executor_internal.h"

static ssize_t	get_next_job_id(t_context *ctx)
{
	ssize_t	id;
	t_job	*curr;

	id = 1;
	while (true)
	{
		curr = ctx->job.head;
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

t_job	*job_create(t_context *ctx, char *cmd_line, bool is_background)
{
	t_job	*job;

	job = x_calloc(1, sizeof(t_job));
	if (!job)
		return (NULL);
	job->job_id = get_next_job_id(ctx);
	job->cmd_line = x_strdup(cmd_line);
	job->is_background = is_background;
	job->capacity = _POSIX_CHILD_MAX;
	job->pids = x_calloc(job->capacity, sizeof(pid_t));
	if (!job->pids)
		return (free(job), NULL);
	return (job);
}
