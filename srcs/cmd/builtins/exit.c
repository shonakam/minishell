/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 21:57:44 by shonakam          #+#    #+#             */
/*   Updated: 2025/02/23 01:19:52 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static int	exit_error(char *arg)
{
	write(2, "minishell: exit: ", 17);
	write(2, arg, ft_strlen(arg));
	write(2, ": numeric argument required\n", 29);
	return (2);
}

int	cmd_exit(t_command *cmd)
{
	int		exit_status;
	char	*s;

	ft_putendl_fd("exit", 2);
	if (cmd->argc == 1)
		exit(0);
	if (cmd->argc >= 2)
	{
		if (!ft_is_numeric(cmd->argv[1]))
			exit(exit_error(cmd->argv[1]));
		else if (cmd->argc == 2)
		{
			exit_status = ft_atoi(cmd->argv[1]) % 256;
			exit(exit_status);
		}
		else
		{
			s = "minishell: exit: too many arguments\n";
			write(2, s, ft_strlen(s));
			return (1);
		}
	}
	return (0);
}
