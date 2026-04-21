#include "session_internal.h"

static void	job_control_destroy(t_job_control *job_ctrl)
{
	t_job	*curr;
	t_job	*next;

	if (!job_ctrl || !job_ctrl->head)
		return ;
	curr = job_ctrl->head;
	while (curr)
	{
		next = curr->next;
		job_free(curr);
		curr = next;
	}
	job_ctrl->head = NULL;
	job_ctrl->current = NULL;
}

void	context_destroy(t_context *ctx)
{
	if (!ctx)
		return ;
	if (ctx->env_list)
	{
		ft_lstclear(&ctx->env_list->next, env_free);
		ft_lstdelone(ctx->env_list, env_free);
	}
	if (ctx->fd_save[0] >= 0)
		close(ctx->fd_save[0]);
	if (ctx->fd_save[1] >= 0)
		close(ctx->fd_save[1]);
	job_control_destroy(&ctx->job);
	ft_memset(ctx, 0, sizeof(t_context));
}
