#include "parser_internal.h"

static t_ast_node	*parse_list_element(
	t_context *ctx, t_list **tokens, t_ast_node *left)
{
	t_token		*op_token;
	t_ast_node	*right;

	op_token = token_consume(tokens);
	if (is_unexpected_at_contextual(ctx, tokens, is_ok_list))
		return (ast_node_free(left), NULL);
	right = parse_logical(ctx, tokens);
	return (ast_node_attach(get_node_type(op_token->type), left, right));
}

t_ast_node	*parse_list(t_context *ctx, t_list **tokens)
{
	t_ast_node	*node;

	node = parse_logical(ctx, tokens);
	if (!node)
		return (NULL);
	while (apply_parser_rule(is_list_op, *tokens))
	{
		node = parse_list_element(ctx, tokens, node);
		if (!node)
			return (NULL);
	}
	return (node);
}
