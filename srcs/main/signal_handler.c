/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 16:46:22 by shonakam          #+#    #+#             */
/*   Updated: 2025/02/13 07:11:38 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	setup_signals(void)
{
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, SIG_IGN);
}

void	observe_signal(t_minishell *mini)
{
	if (g_signal_flag & (1 << 0))
	{
		mini->status = 130;
		g_signal_flag &= ~(1 << 0);
	}
}

void	quit_message(void)
{
	write(STDOUT_FILENO, "\b\b", 2);
	ft_putendl_fd("^\\Quit: 3", STDOUT_FILENO);
}

int	handle_heredoc_signal(void)
{
	if (g_signal_flag & (1 << 7))
	{
		write(STDOUT_FILENO, "\n", 1);
		rl_replace_line("", 0);
		rl_redisplay();
		rl_done = 0;
	}
	return (0);
}

void	handle_signal(int sig)
{
	if (sig == SIGINT)
	{
		g_signal_flag |= (1 << 0);
		if (g_signal_flag & (1 << 2))
		{
			write(STDOUT_FILENO, "\n", 1);
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		}
		else if (g_signal_flag & (1 << 3))
		{
			g_signal_flag |= (1 << 7);
			g_signal_flag |= (1 << 3);
			rl_done = 1;
		}
	}
	else if (sig == SIGQUIT)
		g_signal_flag |= (1 << 1);
}
