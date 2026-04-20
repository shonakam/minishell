#include "parser_internal.h"

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
	if (node->type == NODE_PIPELINE)
		pipeline_free(node->data.pipeline);
	else if (node->type == NODE_SUBSHELL)
		subshell_free(node->data.subshell);
	else if (node->type == NODE_COMMAND || node->type == NODE_BACKGROUND)
		simple_command_free(node->data.command);
	free(node);
}