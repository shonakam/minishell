#include "executor_internal.h"

void	exec_engine(t_context *ctx, t_ast_node *node)
{
	static t_engine_func	engines[NODE_SIZE] = {NULL};

	engines[NODE_PIPELINE] = exec_pipeline;
	engines[NODE_SUBSHELL] = exec_subshell;
	engines[NODE_COMMAND] = exec_command;
	engines[NODE_BACKGROUND] = exec_background;
	engines[NODE_AND] = traverse_ast;
	engines[NODE_OR] = traverse_ast;
	engines[NODE_SEMICOLON] = traverse_ast;
	if (!node)
		return ;
	if (node->type < NODE_SIZE && engines[node->type])
		engines[node->type](ctx, node);
}
