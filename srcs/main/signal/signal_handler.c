/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 16:46:22 by shonakam          #+#    #+#             */
/*   Updated: 2025/02/18 14:04:09 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	setup_signals(void)
{
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, SIG_IGN);
}

int	observe_sigint(char *line, int bit)
{
	if (g_signal_flag & (1 << bit))
	{
		g_signal_flag &= ~(1 << bit);
		if (line)
			free(line);
		return (1);
	}
	return (0);
}

void	quit_message(void)
{
	write(STDOUT_FILENO, "\b\b", 2);
	ft_putendl_fd("^\\Quit: 3", STDOUT_FILENO);
}

void	handle_signal(int sig)
{
	if (sig == SIGINT)
	{
		g_signal_flag |= (1 << 1);
		if (g_signal_flag & (1 << 2))
		{
			g_signal_flag &= ~(1 << 2);
			g_signal_flag |= (1 << 6);
			rl_done = 1;
		}
		else if (g_signal_flag & (1 << 3))
		{
			g_signal_flag &= ~(1 << 3);
			g_signal_flag |= (1 << 7);
			rl_done = 1;
		}
	}
}
