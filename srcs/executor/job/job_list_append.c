#include "../executor_internal.h"

void	job_list_append(t_context *ctx, t_job *new_job)
{
	t_job	*curr;

	if (!ctx->job.head)
		ctx->job.head = new_job;
	else
	{
		curr = ctx->job.head;
		while (curr->next)
			curr = curr->next;
		curr->next = new_job;
	}
	ctx->job.current = new_job;
}
