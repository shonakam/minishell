#include "../executor_internal.h"

void	oneshot(t_context *ctx, t_ast_node *node)
{
	t_simple_command	*cmd;
	t_builtin_func		f;
	char				**argv;

	signal_set_mode(SIG_MODE_CHILD);
	if (node->type == NODE_SUBSHELL)
	{
		exec_engine(ctx, node->left);
		exit(ctx->last_status);
	}
	cmd = node->data.command;
	if (!expand_command(ctx, cmd))
		exit(EXIT_FAILURE);
	if (!redirect_apply(cmd->redirects))
		exit(EXIT_FAILURE);
	argv = convert_args_to_argv(cmd->args);
	if (!argv || !argv[0])
		exit(EXIT_SUCCESS);
	f = get_builtin_func(ctx, argv[0]);
	if (f)
		exit(f(ctx, argv));
	invoke_execve(ctx, argv);
}
