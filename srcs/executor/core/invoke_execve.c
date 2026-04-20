#include "../executor_internal.h"

void	invoke_execve(t_context *ctx, t_simple_command *cmd)
{
	char	*path;
	char	**argv;
	char	**envp;

	argv = convert_args_to_argv(cmd->args);
	if (!cmd->args)
		return ((void)(free_matrix(argv), exit(EXIT_SUCCESS)));
	path = find_path(argv[0], ctx);
	if (!path)
	{
		ft_dprintf(STDERR_FILENO, ERR_CMD_NOT_FOUND, argv[0]);
		exit(STATUS_COMMAND_NOT_FOUND);
	}
	envp = env_serialize(ctx->env_list);
	if (!envp || execve(path, argv, envp) == -1)
	{
		ft_dprintf(STDERR_FILENO, ERR_EXECVE, argv[0], strerror(errno));
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}
