#include "../parser_internal.h"

bool	is_unexpected_at_start(t_context *ctx, t_list **tokens)
{
	t_token	*t;

	if (!tokens || !*tokens)
		return (true);
	t = token_peek(tokens);
	if (is_control_op(t->type) || is_subshell_end(t->type))
	{
		parser_syntax_error(ctx, t->str);
		return (true);
	}
    return (false);
}

bool	is_unexpected_at_end(t_context *ctx, t_list **tokens)
{
	t_token	*t;

	if (!tokens || !*tokens)
		return (true);
	t = token_peek(tokens);
	if (is_control_op(t->type) || is_io(t->type) || is_subshell_start(t->type))
	{
		parser_syntax_error(ctx, t->str);
		return (true);
	}
	return (false);
}

bool	is_unexpected_at_contextual(
	t_context *ctx, t_list **tokens, t_token_rule is_ok)
{
	t_token	*next;

	next = token_peek(tokens);
	printf("DEBUG: %s\r\n", next->str);
	if (!next || !is_ok(next->type))
	{
		parser_syntax_error(ctx, next->str);
		return (true);
	}
	return (false);
}

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
