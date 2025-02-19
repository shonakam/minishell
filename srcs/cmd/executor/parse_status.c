/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_status.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 09:50:44 by shonakam          #+#    #+#             */
/*   Updated: 2025/02/09 04:28:38 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static int	ft_wifexited(int status)
{
	return ((status & 0x7f) == 0);
}

static int	ft_wexitstatus(int status)
{
	return ((status >> 8) & 0xff);
}

static int	ft_wifsignaled(int status)
{
	return ((status & 0x7f) != 0 && (status & 0x7f) != 0x7f);
}

static int	ft_wtermsig(int status)
{
	return (status & 0x7f);
}

int	parse_exit_status(int status)
{
	int	exit_code;

	if (ft_wifexited(status))
	{
		exit_code = ft_wexitstatus(status);
		return (exit_code);
	}
	else if (ft_wifsignaled(status))
	{
		exit_code = ft_wtermsig(status) + 128;
		return (exit_code);
	}
	else
		return (-1);
}
