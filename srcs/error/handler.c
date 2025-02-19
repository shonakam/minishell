/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 21:16:00 by shonakam          #+#    #+#             */
/*   Updated: 2025/02/20 00:02:14 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	handle_file_not_found(
		const char *cmd, const char *path, t_minishell *mini)
{
	(void)path;
	if (cmd[0] != '/'
		&& (ft_strlen(cmd) > 1
			&& cmd[0] != '.'
			&& cmd[1] != '/'))
	{
		print_exec_error(cmd, ": command not found", 127, mini);
	}
	else
	{
		print_exec_error(cmd, ": No such file or directory", 127, mini);
	}
	return (1);
}

int	handle_file_type_error(
		const char *cmd, const char *path, struct stat sb, t_minishell *mini)
{
	if (S_ISDIR(sb.st_mode))
		print_exec_error(cmd, ": Is a directory", 126, mini);
	else if (S_ISREG(sb.st_mode))
	{
		if (access(path, X_OK) == -1)
			print_exec_error(cmd, ": Permission denied", 126, mini);
		else
			return (0);
	}
	else if (S_ISLNK(sb.st_mode))
		print_exec_error(cmd, ": Unknown file type", 127, mini);
	else
		print_exec_error(cmd, ": Not a directory", 127, mini);
	return (1);
}
