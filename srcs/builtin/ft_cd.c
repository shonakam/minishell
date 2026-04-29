#include "builtin_internal.h"

static void	update_pwd_env(t_context *ctx)
{
	char	cwd[PATH_MAX];
	char	*old_pwd;

	old_pwd = env_get_value(ctx->env_list, "PWD");
	if (old_pwd)
	{
		env_set_pair(&ctx->env_list, "OLDPWD", old_pwd);
		free(old_pwd);
	}
	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		env_set_pair(&ctx->env_list, "PWD", cwd);
	}
}

static int	resolve_cd_path(t_context *ctx, char **argv, char **path)
{
	if (argv[1] && argv[2])
		return (ft_dprintf(STDERR_FILENO,
				ERR_TOO_MANY_ARGS, "cd"), EXIT_FAILURE);
	if (argv[1] == NULL)
	{
		*path = env_get_value(ctx->env_list, "HOME");
		if (!(*path))
			return (ft_dprintf(STDERR_FILENO, ERR_CD_HOME), EXIT_FAILURE);
	}
	else if (ft_strncmp(argv[1], "-", 1) == 0)
	{
		*path = env_get_value(ctx->env_list, "OLDPWD");
		if (!(*path))
			return (ft_dprintf(STDERR_FILENO, ERR_CD_OLDPWD), EXIT_FAILURE);
		ft_printf("%s\n", *path);
	}
	else
		*path = x_strdup(argv[1]);
	return (EXIT_SUCCESS);
}

int	ft_cd(t_context *ctx, char **argv)
{
	char	*path;

	if (resolve_cd_path(ctx, argv, &path) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (chdir(path) != 0)
	{
		ft_dprintf(STDERR_FILENO, PROGRAM_NAME ": cd: %s: %s\n",
			path, strerror(errno));
		return (EXIT_FAILURE);
	}
	else
		update_pwd_env(ctx);
	free(path);
	return (EXIT_SUCCESS);
}
