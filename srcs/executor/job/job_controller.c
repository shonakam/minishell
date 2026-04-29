#include "../executor_internal.h"

void	job_register(t_context *ctx, t_job *job)
{
	if (!ctx || !job)
		return ;
	job->next = ctx->job.all;
	ctx->job.all = job;
	if (ctx->job.current != job)
	{
		ctx->job.previous = ctx->job.current;
		ctx->job.current = job;
	}
	if (job->is_background)
		ctx->job.fg = NULL;
	else
		ctx->job.fg = job;
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
			*curr = tmp->next;
			if (ctx->job.fg == tmp)
				ctx->job.fg = NULL;
			if (ctx->job.current == tmp)
				ctx->job.current = ctx->job.previous;
			if (ctx->job.previous == tmp)
				ctx->job.previous = NULL;
			return ((void)job_free(tmp));
		}
		curr = &((*curr)->next);
	}
}

void	job_clear_all(t_context *ctx)
{
	t_job	*curr;
	size_t	i;

	while (ctx->job.all)
	{
		i = 0;
		curr = ctx->job.all;
		while (i < curr->count)
		{
			if (curr->pids[i] > 0)
				kill(curr->pids[i], SIGHUP);
			i++;
		}
		job_discard(ctx, curr);
	}
	ctx->job.all = NULL;
	ctx->job.fg = NULL;
	ctx->job.current = NULL;
	ctx->job.previous = NULL;
}
