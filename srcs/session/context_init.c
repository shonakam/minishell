#include "session_internal.h"

bool	context_init(t_context *ctx, char **envp)
{
	ft_memset(ctx, 0, sizeof(t_context));
	ctx->job.id_counter = 1;
	ctx->fd_save[0] = -1;
	ctx->fd_save[1] = -1;
	ctx->env_list = env_load(envp);
	if (!ctx->env_list)
		return (false);
	if (!update_shlvl(ctx->env_list))
		return (false);
	if (!builtin_table_init(ctx))
		return (false);
	ctx->last_status = 0;
	return (true);
}
