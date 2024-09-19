/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 21:56:25 by shonakam          #+#    #+#             */
/*   Updated: 2024/09/18 06:40:12 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

// argv[1] = -n(nn~~n) -> flag on
// argv[2~] skip -n(nn~~n)
static int	option_parse(char **av, int *index)
{
	int	j;
	int	i;

	i = 1;
	while (av[i] && av[i][0] == '-')
	{
		j = 1;
		while (av[i][j] == 'n')
			j++;
		if (av[i][j] != '\0')
			break;
		i++;
	}
	*index = i;
	return (i > 1);
}

int	cmd_echo(t_command *cmd, int fd)
{
	int	i;
	int	f;

	f = option_parse(cmd->argv, &i);
	while (cmd->argv[i])
	{
		ft_putstr_fd(cmd->argv[i], fd);
		if (cmd->argv[i + 1])
			write(fd, " ", 1);
		i++;
	}
	if (!f)
		write(fd, "\n", 1);
	return (0);
}
