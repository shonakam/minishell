/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 21:57:03 by shonakam          #+#    #+#             */
/*   Updated: 2024/09/15 14:53:01 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

// 変数名はアルファベットまたはアンダースコアで始まるべき
// 残りの文字はアルファベット、数字、またはアンダースコア
// '='はスキップ
static int	is_valid_identifier(const char *str)
{
	if (!str || !*str)
		return (0);
	if (!ft_isalpha(*str) && *str != '_')
		return (0);
	str++;
	while (*str)
	{
		if (!ft_isalnum(*str) && *str != '_')
		{
			if (*str != '=')
				return (0);
		}
		str++;
	}
	return (1);
}

static void	set_all_args(t_command *cmd, int fd, t_envlist *envlist)
{
	char	**kv;
	int		i;

	i = 1;
	while (cmd->argv[i])
	{
		if (!ft_strchr(cmd->argv[i], '=') && i == 1)
		{
			ft_putstr_fd("bash: export: `", fd);
			ft_putstr_fd(cmd->argv[i], fd);
			ft_putendl_fd("': not a valid identifier", fd);
		}
		else if (is_valid_identifier(cmd->argv[i]))
		{
			printf("\033[31mBREAKPOINT\033[0m\n");
			kv = ft_split_by_eq(cmd->argv[i]);
			if (kv)
			{
				ft_putenv(&envlist, kv[0], kv[1]);
				free(kv[0]);
				free(kv[1]);
				free(kv);
			}
		}
		i++;
	}
}

// 引数がない場合、環境変数の一覧を表示
int	cmd_export(t_command *cmd, int fd, t_envlist *envlist)
{
	char		**kv;
	int			i;

	i = 0;
	if (!cmd->argv[1])
	{
		kv = convert_to_envp(&envlist);
		while (kv[i])
		{
			ft_putstr_fd("declare -x ", fd);
			ft_putendl_fd(kv[i], fd);
			free(kv[i++]);
		}
		return (free(kv),0);
	}
	else
	{
		set_all_args(cmd, fd, envlist);
	}
	return (0);
}
