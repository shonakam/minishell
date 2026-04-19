#include "utils_internal.h"

void	safe_exit(t_context *ctx, int status)
{
	if (ctx->env_list)
		ft_lstclear(&ctx->env_list, env_free);
	if (ctx->fd_save[0] != -1)
		close(ctx->fd_save[0]);
	if (ctx->fd_save[1] != -1)
		close(ctx->fd_save[1]);
	exit(status);
}

