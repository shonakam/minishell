#include "parser_internal.h"

/*
 * It must call parse_list to allow the full command grammar
 * (including ; and &) inside the parentheses.
 */
t_ast_node	*parse_subshell(t_context *ctx, t_list **tokens)
{
	t_ast_node	*inner_ast;
	t_ast_node	*node;

	token_consume(tokens);
	inner_ast = parse_list(ctx, tokens);
	if (!inner_ast)
		return (NULL);
	if (is_unexpected_at_contextual(ctx, tokens, is_subshell_end))
		return (ast_node_free(inner_ast), NULL);
	token_consume(tokens);
	node = ast_node_new(NODE_SUBSHELL);
	if (!node)
		return (ast_node_free(inner_ast), NULL);
	node->left = inner_ast;
	return (node);
}
