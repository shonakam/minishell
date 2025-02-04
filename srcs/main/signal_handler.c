/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 16:46:22 by shonakam          #+#    #+#             */
/*   Updated: 2025/02/04 10:24:51 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void setup_signals(void)
{
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, SIG_IGN);
}

int	observe_signal(t_minishell *mini)
{
	if (g_signal_flag & SIGINT_FLAG)
	{
		mini->status = 130;
		g_signal_flag &= ~SIGINT_FLAG;
		return (1);
	}
	if (g_signal_flag & SIGQUIT_FLAG)
	{
		mini->status = 131;
		g_signal_flag &= ~SIGQUIT_FLAG;
		return (1);
	}
	return (0);
}

void handle_signal(int sig)
{
	if (sig == SIGINT)
	{
		g_signal_flag |= SIGINT_FLAG;
		write(STDOUT_FILENO, "\n", 1);
		if (g_signal_flag & IN_READLINE)
		{
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		}
	}
	else if (sig == SIGQUIT)
		g_signal_flag |= SIGQUIT_FLAG;
}
