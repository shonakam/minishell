#include "parser_internal.h"

static t_ast_node	*parse_list_element(
	t_context *ctx, t_list **tokens, t_ast_node *left)
{
	t_token		*op_token;
	t_ast_node	*right;
	t_node_type	type;

	op_token = token_consume(tokens);
	if (!is_unexpected_at_contextual(ctx, tokens, is_command_start))
		return (ast_node_free(left), NULL);
	right = parse_logical(ctx, tokens);
	if (!right &&  is_list_op(op_token->type))
		return (ast_node_attach(get_node_type(op_token->type), left, NULL));
	if (!right)
		return (ast_node_free(left), NULL);
	type = get_node_type(op_token->type);
	return (ast_node_attach(type, left, right));
}

t_ast_node	*parse_list(t_context *ctx, t_list **tokens)
{
	t_ast_node	*node;

	node = parse_logical(ctx, tokens);
	if (!node)
		return (NULL);
	while (*tokens)
	{
		if (apply_parser_rule(is_eof, *tokens))
		{
			token_consume(tokens);
			continue ;
		}
		if (!apply_parser_rule(is_list_op, *tokens))
			break ;
		if (!is_unexpected_at_contextual(ctx, tokens, is_command_start))
			return (ast_node_free(node), NULL);
		node = parse_list_element(ctx, tokens, node);
		if (!node)
			return (NULL);
	}
	return (node);
}
