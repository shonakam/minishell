#include "builtin_internal.h"

int	ft_pwd(t_context *ctx, char **argv)
{
	char	cwd[PATH_MAX];
	char	*pwd_env;

	(void)argv;
	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		ft_putendl_fd(cwd, STDOUT_FILENO);
		return (EXIT_SUCCESS);
	}
	pwd_env = env_get_value(ctx->env_list, "PWD");
	if (pwd_env)
	{
		ft_putendl_fd(pwd_env, STDOUT_FILENO);
		free(pwd_env);
		return (EXIT_SUCCESS);
	}
	ft_dprintf(STDERR_FILENO, "%s: %s\n", ERR_PWD_GETCWD, strerror(errno));
	return (EXIT_FAILURE);
}
