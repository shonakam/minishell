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
	job_clear_all(ctx);
	scope_clear(&ctx->scope);
	ft_history_destroy();
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
	exit(status);
}
