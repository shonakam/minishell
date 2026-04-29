#include "parser_internal.h"

static t_ast_node	*parse_logical_element(
	t_context *ctx, t_list **tokens, t_ast_node *left)
{
	t_token		*op_token;
	t_ast_node	*right;

	op_token = token_consume(tokens);
	if (is_unexpected_at_contextual(ctx, tokens, is_command_start))
		return (ast_node_free(left), NULL);
	right = parse_pipeline(ctx, tokens);
	if (!right)
		return (ast_node_free(left), NULL);
	return (ast_node_attach(get_node_type(op_token->type), left, right));
}

t_ast_node	*parse_logical(t_context *ctx, t_list **tokens)
{
	t_ast_node	*node;

	node = parse_pipeline(ctx, tokens);
	if (!node)
		return (NULL);
	while (apply_parser_rule(is_logical_op, *tokens))
	{
		node = parse_logical_element(ctx, tokens, node);
		if (!node)
			return (NULL);
	}
	return (node);
}
