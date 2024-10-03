/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 16:46:22 by shonakam          #+#    #+#             */
/*   Updated: 2024/10/02 20:01:46 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	setup_signals(void)
{
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, handle_signal);
}

/*
-- ctrl + C -> 130
-- ctrl + \ -> 131
*/
int	observe_signal(t_minishell *mini)
{
	if (g_signal_flag)
	{
		if (g_signal_flag == 0b00000001)
			mini->status = 130;
		else if (g_signal_flag == 0b00000010)
			mini->status = 131;
		g_signal_flag = 0b00000000;
		return (1);
	}
	return (0);
}

/*
-- 1 -> ctrl + C
-- 2 -> ctrl + \
*/
void	handle_signal(int sig)
{
	if (sig == SIGINT)
	{
		// if (g_signal_flag == 0)
		rl_on_new_line();
		rl_replace_line("", 0);
		write(STDOUT_FILENO, "\n", 1);
		rl_redisplay();
		g_signal_flag |= (0b00000001 << 0);
	}
	else if (sig == SIGQUIT)
	{
		if (g_signal_flag == 0)
			return ;
		kill(g_signal_flag, SIGQUIT);
		// printf("kill-->[%d]\n", g_signal_flag);
		g_signal_flag |= (0b00000001 << 1);
		ft_putstr_fd("Quit: ", STDOUT_FILENO);
		ft_putendl_fd(ft_itoa(SIGQUIT), STDOUT_FILENO);
	}
}
