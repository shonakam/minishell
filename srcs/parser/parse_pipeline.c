#include "parser_internal.h"

static t_ast_node	*create_pipeline_node(t_ast_node *left, t_ast_node *right)
{
	t_ast_node	*node;

	if (!right)
		return (ast_node_free(left), NULL);
	node = ast_node_new(NODE_PIPELINE);
	if (!node)
	{
		ast_node_free(left);
		ast_node_free(right);
		return (NULL);
	}
	node->left = left;
	node->right = right;
	return (node);
}

t_ast_node	*parse_pipeline(t_context *ctx, t_list **tokens)
{
	t_ast_node	*node;
	t_ast_node	*right;

	node = parse_command(ctx, tokens);
	if (!node)
		return (NULL);
	while (*tokens)
	{
		if (token_peek_type(tokens) != TOKEN_PIPE)
			break ;
		token_consume(tokens);
		if (!is_unexpected_at_contextual(ctx, tokens, is_ok_pipeline))
			return (ast_node_free(node), NULL);
		right = parse_command(ctx, tokens);
		node = create_pipeline_node(node, right);
		if (!node)
			return (NULL);
	}
	return (node);
}
