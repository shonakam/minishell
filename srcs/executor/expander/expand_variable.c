#include "../executor_internal.h"

bool	expand_variable(t_context *ctx, t_simple_command *cmd)
{
	t_list	*curr;
	t_list	*prev;

	if (!cmd || !cmd->args)
		return (true);
	curr = cmd->args;
	prev = NULL;
	while (curr)
	{
		if (!handle_node_expansion(ctx, cmd, &curr, &prev))
			return (false);
	}
	return (true);
}
