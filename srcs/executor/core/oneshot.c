#include "../executor_internal.h"

void	invoke_execve(t_context *ctx, char **argv)
{
	char	*path;
	char	**envp;

	path = find_path(argv[0], ctx);
	if (!path)
	{
		ft_dprintf(STDERR_FILENO, ERR_CMD_NOT_FOUND, argv[0]);
		safe_exit(ctx, NULL, argv, STATUS_COMMAND_NOT_FOUND);
	}
	envp = env_serialize(ctx->env_list);
	if (!envp || execve(path, argv, envp) == -1)
	{
		free(path);
		ft_dprintf(STDERR_FILENO, ERR_EXECVE, argv[0], strerror(errno));
		safe_exit(ctx, envp, argv, EXIT_FAILURE);
	}
	safe_exit(ctx, envp, argv, EXIT_SUCCESS);
}

void	oneshot(t_context *ctx, t_ast_node *node)
{
	t_simple_command	*cmd;
	t_builtin_func		f;
	char				**argv;

	termios_ctl(false);
	signal_set_mode(SIG_MODE_CHILD);
	if (node->type == NODE_SUBSHELL)
	{
		if (node->redirects && !redirect_apply(node->redirects))
			return (safe_exit(ctx, NULL, NULL, EXIT_FAILURE));
		exec_engine(ctx, node->left);
		safe_exit(ctx, NULL, NULL, ctx->last_status);
	}
	cmd = node->data.command;
	if (!expand_command(ctx, cmd))
		return (safe_exit(ctx, NULL, NULL, EXIT_FAILURE));
	if (!redirect_apply(cmd->redirects))
		return (safe_exit(ctx, NULL, NULL, EXIT_FAILURE));
	argv = convert_args_to_argv(cmd->args);
	if (!argv || !argv[0])
		return (safe_exit(ctx, NULL, argv, EXIT_SUCCESS));
	f = get_builtin_func(ctx, argv[0]);
	if (f)
		safe_exit(ctx, NULL, argv, f(ctx, argv));
	invoke_execve(ctx, argv);
}
