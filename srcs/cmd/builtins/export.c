/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 21:57:03 by shonakam          #+#    #+#             */
/*   Updated: 2025/02/18 19:56:38 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static void set_only_key(char *key, t_envlist *envlist)
{
	if (!key)
		return ;
	ft_putenv(&envlist, key, "");
}

static void	set_all_args(t_command *cmd, int fd, t_envlist *envlist)
{
	char	**kv;
	int		i;

	i = 1;
	while (cmd->argv && cmd->argv[i])
	{
		kv = ft_split_by_eq(cmd->argv[i]);
		if (kv)
		{
			if (!is_valid_key(kv[0]))
			{
				ft_putstr_fd("bash: export: `", fd);
				ft_putstr_fd(kv[0], fd);
				ft_putendl_fd("': not a valid identifier", fd);
			}
			else
				ft_putenv(&envlist, kv[0], kv[1]);
			free(kv[0]);
			free(kv[1]);
			free(kv);
		}
		else
			set_only_key(cmd->argv[i], envlist);
		i++;
	}
}

int	cmd_export(t_command *cmd, int fd, t_envlist *envlist)
{
	char		**kv;
	int			i;

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
	else
		set_all_args(cmd, fd, envlist);
	return (0);
}
