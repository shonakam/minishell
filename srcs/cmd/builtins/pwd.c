/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 21:56:47 by shonakam          #+#    #+#             */
/*   Updated: 2024/09/14 20:06:53 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	cmd_pwd(t_command *cmd, int fd)
{
	char	cwd[PATH_MAX];
	char	*s;

	(void)cmd;
	// if (cmd->argc > 1)
	// {
	// 	s = "pwd: too many arguments\n";
	// 	write(2, s, ft_strlen(s));
	// }
	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		s = concat_vars(2, cwd, "\n");
		write(fd, s, ft_strlen(s));
		free(s);
		return (0);
	}
	else
	{
		s = "pwd: too many arguments\n";
		write(2, s, ft_strlen(s));
	}
	return (1);
}