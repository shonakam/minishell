#include "session_internal.h"

void	context_destroy(t_context *ctx)
{
	if (!ctx)
		return ;
	scope_clear(&ctx->scope);
	if (ctx->env_list)
	{
		ft_lstclear(&ctx->env_list->next, env_free);
		ft_lstdelone(ctx->env_list, env_free);
	}
	if (ctx->fd_save[0] >= 0)
		close(ctx->fd_save[0]);
	if (ctx->fd_save[1] >= 0)
		close(ctx->fd_save[1]);
	job_clear_all(ctx);
	ft_memset(ctx, 0, sizeof(t_context));
}
