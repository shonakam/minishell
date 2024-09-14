/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 21:56:15 by shonakam          #+#    #+#             */
/*   Updated: 2024/09/14 21:38:17 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	cmd_cd(t_command *cmd)
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
	if (chdir(path) != 0)
	{
		s = concat_vars(4, "cd: ", path, ": ", "\n");
		ft_putstr_fd(strerror(errno), STDERR_FILENO); // エラーメッセージ出力
		return (free(s), 1);
	}
	return (0);
}
