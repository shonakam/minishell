#include "../parser_internal.h"

t_ast_node	*ast_node_new(t_node_type type)
{
	t_ast_node	*node;

	node = (t_ast_node *)x_calloc(1, sizeof(t_ast_node));
	if (!node)
		return (NULL);
	node->type = type;
	return (node);
}

/*
* Recursively frees the AST nodes and all associated data.
* Uses post-order traversal (left, right, then current node).
*/
void	ast_node_free(t_ast_node *node)
{
	if (!node)
		return ;
	ast_node_free(node->left);
	ast_node_free(node->right);
	if (node->redirects)
		ft_lstclear(&node->redirects, (void *)redirect_free);
	if (node->type == NODE_PIPELINE)
		pipeline_free(node->data.pipeline);
	else if (node->type == NODE_SUBSHELL)
		subshell_free(node->data.subshell);
	else if (node->type == NODE_COMMAND || node->type == NODE_BACKGROUND)
		simple_command_free(node->data.command);
	free(node);
}

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

bool	ast_node_is_empty(t_ast_node *node)
{
	if (!node)
		return (true);
	if (node->type == NODE_COMMAND)
		return (simple_command_is_empty(node->data.command));
	if (node->type == NODE_PIPELINE
		|| node->type == NODE_AND
		|| node->type == NODE_OR)
		return (pipeline_is_empty(node->data.pipeline));
	if (node->type == NODE_SUBSHELL)
		return (subshell_is_empty(node->data.subshell));
	return (false);
}
