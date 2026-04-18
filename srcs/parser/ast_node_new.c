#include "parser_internal.h"

t_ast_node	*ast_node_new(t_node_type type)
{
	t_ast_node	*node;

	node = (t_ast_node *)x_calloc(1, sizeof(t_ast_node));
	if (!node)
		return (NULL);
	node->type = type;
	return (node);
}
