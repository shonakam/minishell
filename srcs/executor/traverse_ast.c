#include "executor_internal.h"

/**
 * Traverses binary operator nodes (&&, ||, ;) in the AST.
 * * Logic follows left-associativity:
 * The left child is executed first, and the right child's execution
 * depends on the node type and the exit status of the left child.
 */
void	traverse_ast(t_context *ctx, t_ast_node *node)
{
	if (!node)
		return;
	exec_engine(ctx, node->left);
	if (node->type == NODE_AND && ctx->last_status != STATUS_SUCCESS)
		return ;
	if (node->type == NODE_OR && ctx->last_status == STATUS_SUCCESS)
		return ;
	exec_engine(ctx, node->right);
}
