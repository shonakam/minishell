/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 00:04:41 by shonakam          #+#    #+#             */
/*   Updated: 2024/09/14 23:47:29 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	is_builtin(t_command *cmd)
{
	if (!ft_strcmp(cmd->argv[0], "cd"))
		return (1);
	else if (!ft_strcmp(cmd->argv[0], "echo"))
		return (1);
	else if (!ft_strcmp(cmd->argv[0], "env"))
		return (1);
	else if (!ft_strcmp(cmd->argv[0], "exit"))
		return (1);
	else if (!ft_strcmp(cmd->argv[0], "export"))
		return (1);
	else if (!ft_strcmp(cmd->argv[0], "pwd"))
		return (1);
	else if (!ft_strcmp(cmd->argv[0], "unset"))
		return (1);
	return (0);
}

// ビルトインコマンドを実行する関数
int	builtin_runner(t_command *cmd, int fd, t_envlist *envlist)
{
	if (!ft_strcmp(cmd->argv[0], "cd"))
		return (cmd_cd(cmd));
	else if (!ft_strcmp(cmd->argv[0], "echo"))
		return (1);
	else if (!ft_strcmp(cmd->argv[0], "env"))
		return (cmd_env(fd, envlist));
	else if (!ft_strcmp(cmd->argv[0], "exit"))
		return (cmd_exit(cmd, fd));
	else if (!ft_strcmp(cmd->argv[0], "export"))
		return (1);
	else if (!ft_strcmp(cmd->argv[0], "pwd"))
		return (cmd_pwd(cmd, fd));
	else if (!ft_strcmp(cmd->argv[0], "unset"))
		return (cmd_unset(cmd, envlist));
	return (127);
}