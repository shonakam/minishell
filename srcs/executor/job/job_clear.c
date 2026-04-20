#include "../executor_internal.h"

void	job_clear(t_context *ctx)
{
	t_job	*curr;
	t_job	*next;

	curr = ctx->job.head;
	while (curr)
	{
		next = curr->next;
		job_free(curr);
		curr = next;
	}
	ctx->job.head = NULL;
	ctx->job.current = NULL;
}
