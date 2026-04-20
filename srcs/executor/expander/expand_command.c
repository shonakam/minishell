#include "../executor_internal.h"

bool	expand_command(t_context *ctx, t_simple_command *cmd)
{
	// t_arg *arg = (t_arg *)cmd->args->content;
	// printf("d1: %s\n", arg->str);
	// arg = (t_arg *)cmd->args->next->content;
	// printf("d2: %s\n", arg->str);
	if (!cmd || !cmd->args)
		return (true);
	if (!expand_variable(ctx, cmd))
		return (false);
	if (!expand_wildcard(cmd))
		return (false);
	if (!remove_quotes(cmd))
		return (false);
	return (true);
}
