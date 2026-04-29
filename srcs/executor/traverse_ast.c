#include "executor_internal.h"

static void	wait_and_discard_job(t_context *ctx)
{
	if (ctx->job.fg)
	{
		job_wait(ctx, ctx->job.fg);
		job_discard(ctx, ctx->job.fg);
		ctx->job.fg = NULL;
	}
}

static void	handle_logical_op(t_context *ctx, t_ast_node *node)
{
	traverse_ast(ctx, node->left);
	wait_and_discard_job(ctx);
	if (node->type == NODE_AND && ctx->last_status != 0)
		return ;
	if (node->type == NODE_OR && ctx->last_status == 0)
		return ;
	traverse_ast(ctx, node->right);
	wait_and_discard_job(ctx);
}

static void	handle_semicolon(t_context *ctx, t_ast_node *node)
{
	traverse_ast(ctx, node->left);
	wait_and_discard_job(ctx);
	traverse_ast(ctx, node->right);
	wait_and_discard_job(ctx);
}

/**
 * Traverses binary operator nodes (&&, ||, ;) in the AST.
 * * Logic follows left-associativity:
 * The left child is executed first, and the right child's execution
 * depends on the node type and the exit status of the left child.
 */
void	traverse_ast(t_context *ctx, t_ast_node *node)
{
	if (!node)
		return ;
	if (node->type == NODE_AND || node->type == NODE_OR)
		handle_logical_op(ctx, node);
	else if (node->type == NODE_SEMICOLON)
		handle_semicolon(ctx, node);
	else
	{
		exec_engine(ctx, node);
		if (!ctx->in_pipeline && ctx->job.fg)
			wait_and_discard_job(ctx);
	}
}
