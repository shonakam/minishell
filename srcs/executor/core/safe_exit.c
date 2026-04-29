#include "../executor_internal.h"

void	safe_exit(t_context *ctx, char **e, char **a, int status)
{
	if (ctx->env_list)
	{
		ft_lstclear(&ctx->env_list->next, env_free);
		ft_lstclear(&ctx->env_list, env_free);
	}
	if (e)
		free_matrix(e);
	if (a)
		free_matrix(a);
	if (ctx->scope.sub_root)
		free(ctx->scope.sub_root);
	job_clear_all(ctx);
	if (ctx->scope.fd_stdio[0] != -1)
		close(ctx->scope.fd_stdio[0]);
	if (ctx->scope.fd_stdio[1] != -1)
		close(ctx->scope.fd_stdio[1]);
	scope_clear(&ctx->scope);
	ft_history_destroy();
	termios_ctl(false);
	exit(status);
}
