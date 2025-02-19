/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 21:57:03 by shonakam          #+#    #+#             */
/*   Updated: 2025/02/20 01:07:20 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static int set_only_key(char *key, t_envlist *envlist)
{
	if (!key)
		return (1);
	if (!is_valid_key(key))
	{
		ft_putstr_fd("bash: export: `", STDERR_FILENO);
		ft_putstr_fd(key,  STDERR_FILENO);
		ft_putendl_fd("': not a valid identifier",  STDERR_FILENO);
		return (1);
	}
	ft_putenv(&envlist, key, "");
	return (0);
}

static int set_kvs(char **kv, t_envlist *envlist)
{
	if (!is_valid_key(kv[0]))
	{
		ft_putstr_fd("bash: export: `", STDERR_FILENO);
		ft_putstr_fd(kv[0],  STDERR_FILENO);
		ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
		return (1);
	}
	else
		ft_putenv(&envlist, kv[0], kv[1]);
	free(kv[0]);
	free(kv[1]);
	free(kv);
	return (0);
}

static int	set_all_args(t_command *cmd, t_envlist *envlist)
{
	char	**kv;
	int		i;
	int		status;

	i = 1;
	status = 0;
	while (cmd->argv && cmd->argv[i])
	{
		kv = ft_split_by_eq(cmd->argv[i]);
		if (kv)
			status += set_kvs(kv, envlist);
		else
			status += set_only_key(cmd->argv[i], envlist);
		i++;
	}
	if (status > 0)
		return (1);
	return (0);
	
}

int	cmd_export(t_command *cmd, int fd, t_envlist *envlist)
{
	char		**kv;
	int			i;

	(void)fd;
	i = 0;
	if (!cmd->argv[1])
	{
		kv = convert_to_envp(&envlist);
		sort_envlist(kv, get_listsize(&envlist), 0, 0);
		while (kv[i])
		{
			ft_putstr_fd("declare -x ", fd);
			ft_putendl_fd(kv[i], fd);
			free(kv[i++]);
		}
		return (free(kv), 0);
	}
	return (set_all_args(cmd, envlist));
}
