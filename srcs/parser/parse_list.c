#include "parser_internal.h"

static t_node_type	token_to_node_type(t_token_type type)
{
	if (type == TOKEN_AND_IF)
		return (NODE_AND);
	if (type == TOKEN_OR_IF)
		return (NODE_OR);
	if (type == TOKEN_AMPERSAND)
		return (NODE_BACKGROUND);
	if (type == TOKEN_SEMICOLON)
		return (NODE_SEMICOLON);
	return (NODE_PIPELINE);
}

static t_ast_node	*parse_list_element(
	t_context *ctx, t_list **tokens, t_ast_node *left)
{
	t_token			*op_token;
	t_ast_node		*right;
	t_node_type		type;

	op_token = token_consume(tokens);
	if (!is_next_token_valid(ctx, tokens, is_ok_list))
		return (ast_node_free(left), NULL);
	right = parse_pipeline(ctx, tokens);
	if (!right &&
			(op_token->type == TOKEN_AMPERSAND ||
			op_token->type == TOKEN_SEMICOLON))
		return (ast_node_attach(
			token_to_node_type(op_token->type), left, NULL));
	if (!right)
		return (ast_node_free(left), NULL);
	type = token_to_node_type(op_token->type);
	return (ast_node_attach(type, left, right));
}

t_ast_node	*parse_list(t_context *ctx, t_list **tokens)
{
	t_ast_node	*node;
	t_token     *token;

	node = parse_pipeline(ctx, tokens);
	if (!node)
		return (NULL);
	while (*tokens)
	{
		token = (t_token *)(*tokens)->content;
		if (!is_logical_operator(token) && !is_list_operator(token))
			break ;
		if (token->type == TOKEN_NEWLINE)
		{
			token_consume(tokens);
			continue ;
		}
		node = parse_list_element(ctx, tokens, node);
		if (!node)
			return (NULL);
	}
	return (node);
}
