#include "../executor_internal.h"

static void	invoke_execve_safe_exit(char **e, char **a)
{
	if (e)
		free_matrix(e);
	if (a)
		free_matrix(a);
}

void	invoke_execve(t_context *ctx, char **argv)
{
	char	*path;
	char	**envp;

	path = find_path(argv[0], ctx);
	if (!path)
	{
		ft_dprintf(STDERR_FILENO, ERR_CMD_NOT_FOUND, argv[0]);
		invoke_execve_safe_exit(NULL, argv);
		exit(STATUS_COMMAND_NOT_FOUND);
	}
	envp = env_serialize(ctx->env_list);
	if (!envp || execve(path, argv, envp) == -1)
	{
		ft_dprintf(STDERR_FILENO, ERR_EXECVE, argv[0], strerror(errno));
		invoke_execve_safe_exit(envp, argv);
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}
