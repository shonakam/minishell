#include "parser_internal.h"

static bool	is_terminator(t_token *token)
{
	if (is_logical_operator(token)
		|| token->type == TOKEN_SEMICOLON
		|| token->type == TOKEN_NEWLINE
		|| token->type == TOKEN_PIPE
		|| token->type == TOKEN_AMPERSAND
		|| token->type == TOKEN_RPAREN
		|| token->type == TOKEN_EOF)
	{
		return (true);
	}
	return (false);
}

static t_ast_node	*wrap_command_node(t_simple_command *cmd)
{
	t_ast_node	*node;

	node = ast_node_new(NODE_COMMAND);
	if (!node)
		return (simple_command_free(cmd), NULL);
	node->data.command = cmd;
	return (node);
}

static bool	append_command_element(
	t_context *ctx, t_simple_command *cmd, t_list **tokens)
{
	t_token	*t;

	t = token_peek(tokens);
	if (is_token_redirect(t))
	{
		if (!is_next_token_valid(ctx, tokens, is_ok_command))
			return (false);
		return (parse_redirect_into_cmd(cmd, tokens));
	}
	if (t->type == TOKEN_WORD)
		return (parse_arg_into_cmd(cmd, tokens));
	return (false);
}

t_ast_node	*parse_command(t_context *ctx, t_list **tokens)
{
	t_simple_command	*cmd;

	if (token_peek(tokens) && (token_peek(tokens))->type == TOKEN_LPAREN)
		return (parse_subshell(ctx, tokens));
	cmd = simple_command_new();
	if (!cmd)
		return (NULL);
	while (*tokens && !is_terminator(token_peek(tokens)))
	{
		if (!append_command_element(ctx, cmd, tokens))
			return (simple_command_free(cmd), NULL);
	}
	if (is_empty_command(cmd))
		return (simple_command_free(cmd), NULL);
	return (wrap_command_node(cmd));
}
