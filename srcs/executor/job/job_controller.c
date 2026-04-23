#include "../executor_internal.h"

void	job_register(t_context *ctx, t_job *job)
{
	if (!ctx || !job)
		return ;
	job->next = ctx->job.all;
	ctx->job.all = job;
	ctx->job.previous = ctx->job.current;
	ctx->job.current = job;
}

void	job_discard(t_context *ctx, t_job *target)
{
	t_job	**curr;
	t_job	*tmp;

	if (!ctx || !target)
		return ;
	curr = &ctx->job.all;
	while (*curr)
	{
		if (*curr == target)
		{
			tmp = *curr;
			*curr = (*curr)->next;
			if (ctx->job.fg == tmp)
				ctx->job.fg = NULL;
			if (ctx->job.current == tmp)
				ctx->job.current = NULL;
			job_free(tmp);
			return ;
		}
		curr = &((*curr)->next);
	}
}

void	job_clear_all(t_context *ctx)
{
	t_job	*curr;
	t_job	*next;

	curr = ctx->job.all;
	while (curr)
	{
		next = curr->next;
		job_free(curr);
		curr = next;
	}
	ctx->job.all = NULL;
	ctx->job.fg = NULL;
	ctx->job.current = NULL;
	ctx->job.previous = NULL;
}
