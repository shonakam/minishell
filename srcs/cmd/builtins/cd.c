/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 21:56:15 by shonakam          #+#    #+#             */
/*   Updated: 2025/02/09 10:51:55 by shonakam         ###   ########.fr       */
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

int	cmd_cd(t_command *cmd, t_envlist *envlist)
{
	const char	*path;
	char		*s;

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
		s = concat_vars(4, "cd: ", path, ": ", "\n");
		ft_putstr_fd(strerror(errno), STDERR_FILENO);
		return (free(s), 1);
	}
	update_pwd(envlist);
	return (0);
}
