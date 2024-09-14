/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 00:04:41 by shonakam          #+#    #+#             */
/*   Updated: 2024/09/14 17:19:28 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	is_builtin(t_command *cmd)
{
	if (!ft_strcmp(cmd->argv[0], "pwd"))
		return (1); // ビルトインコマンドであると示す
	else if (!ft_strcmp(cmd->argv[0], "exit"))
		return (1); // ビルトインコマンドであると示す
	// 他のビルトインコマンドのチェックを追加
	return (0); // ビルトインコマンドでない
}

// ビルトインコマンドを実行する関数
int	builtin_runner(t_command *cmd, int fd)
{
	if (!ft_strncmp(cmd->argv[0], "pwd", ft_strlen(cmd->argv[0])))
		return (cmd_pwd(cmd, fd));
	else if (!ft_strncmp(cmd->argv[0], "exit", ft_strlen(cmd->argv[0])))
		return (cmd_exit(cmd, fd));
	// 他のビルトインコマンドの実行を追加
	return (127); // コマンドが見つからない場合のエラーコード
}