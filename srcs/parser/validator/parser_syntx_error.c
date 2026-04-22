#include "../parser_internal.h"

/**
 * Handle syntax errors by reporting to the user and updating the context.
 * In a recursive descent parser, setting a flag helps to skip further
 * processing and return NULL back up to the root.
 */
void	parser_syntax_error(t_context *ctx, char *token)
{
	ft_dprintf(STDERR_FILENO, ERR_SYNTAX_TOKEN, token);
	ctx->last_status = STATUS_SYNTAX_ERR;
}
