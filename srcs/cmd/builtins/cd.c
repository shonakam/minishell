/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 21:56:15 by shonakam          #+#    #+#             */
/*   Updated: 2025/02/20 00:30:34 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static void	update_oldpwd(t_envlist *envlist)
{
	char	*old;
	char	*key1;
	char	*key2;

	key1 = "PWD";
	key2 = "OLDPWD";
	old = ft_getenv(envlist, key1);
	ft_putenv(&envlist, key2, old);
}

static void	update_pwd(t_envlist *envlist)
{
	char	cwd[PATH_MAX];
	char	*key;

	key = "PWD";
	if (getcwd(cwd, sizeof(cwd)) != NULL)
		ft_putenv(&envlist, key, cwd);
	else
		perror("minishell: getcwd failed");
}

static char	*faild_cd_msg(const char *path)
{
	char	*tmp;
	char	*result;

	tmp = ft_strjoin("cd: ", path);
	result = ft_strjoin(tmp, ": ");
	free(tmp);
	return (result);
}

int	cmd_cd(t_command *cmd, t_envlist *envlist)
{
	const char	*path;
	char		*faild;

	if (cmd->argv[1] == NULL)
	{
		path = getenv("HOME");
		if (path == NULL)
		{
			ft_putstr_fd("cd: HOME not set\n", STDERR_FILENO);
			return (1);
		}
	}
	else
		path = cmd->argv[1];
	update_oldpwd(envlist);
	if (chdir(path) != 0)
	{
		faild = faild_cd_msg(path);
		print_exec_error(faild, strerror(errno), 1, NULL);
		free(faild);
		return (1);
	}
	update_pwd(envlist);
	return (0);
}
