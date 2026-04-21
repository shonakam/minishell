#include "parser_internal.h"

static t_node_type	get_node_type(t_token_type type)
{
	if (type == TOKEN_AND_IF)
		return (NODE_AND);
	return (NODE_OR);
}

static t_ast_node	*parse_logical_ops(t_context *ctx, t_list **tokens)
{
	t_ast_node	*node;
	t_token		*op;
	t_ast_node	*new_node;

	node = parse_pipeline(ctx, tokens);
	while (token_peek(tokens)
		&& is_logical_operator((t_token *)(*tokens)->content))
	{
		op = token_consume(tokens);
		new_node = ast_node_new(get_node_type(op->type));
		if (!new_node)
			return (ast_node_free(node), NULL);
		new_node->left = node;
		new_node->right = parse_pipeline(ctx, tokens);
		node = new_node;
	}
	return (node);
}

t_ast_node	*parse_subshell(t_context *ctx, t_list **tokens)
{
	t_ast_node	*inner_ast;
	t_ast_node	*node;

	token_consume(tokens);
	inner_ast = parse_logical_ops(ctx, tokens);
	if (!inner_ast)
		return (NULL);
	if (!token_peek(tokens) || token_peek(tokens)->type != TOKEN_RPAREN)
		return (ast_node_free(inner_ast), NULL);
	token_consume(tokens);
	node = ast_node_new(NODE_SUBSHELL);
	if (!node)
		return (ast_node_free(inner_ast), NULL);
	node->left = inner_ast;
	return (node);
}
