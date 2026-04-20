#include "executor_internal.h"

int	executor(t_context *ctx, t_ast_node *ast)
{
	int	hd_index;

	hd_index = 0;
	if (heredoc_prepare_all(ctx, ast, &hd_index) == false)
		return (STATUS_SIGINT);
	if (!ast)
		return (EXIT_SUCCESS);
	exec_engine(ctx, ast);
	return (ctx->last_status);
}
