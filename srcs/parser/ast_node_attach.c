#include "parser_internal.h"

t_ast_node	*ast_node_attach(
	t_node_type type, t_ast_node *left, t_ast_node *right)
{
	t_ast_node	*node;

	node = ast_node_new(type);
	if (!node)
		return (NULL);
	node->left = left;
	node->right = right;
	return (node);
}
