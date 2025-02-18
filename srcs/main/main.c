/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 09:01:24 by shonakam          #+#    #+#             */
/*   Updated: 2025/02/18 15:22:54 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

/* 
-- [1 << 1] SIG_INT
-- [1 << 2] in_mainprompt
-- [1 << 3] in_heredoc
-- [1 << 4] ###
-- [1 << 5] ###
-- [1 << 6] event_hook_main
-- [1 << 7] event_hook_heredoc
*/
volatile sig_atomic_t	g_signal_flag = 0b00000000;

static t_minishell	*init_mini(char **envp)
{
	t_minishell	*mini;

	mini = malloc(sizeof(t_minishell));
	if (!mini)
		return (NULL);
	mini->line = NULL;
	mini->token = NULL;
	mini->cmd = NULL;
	mini->in_fd = STDIN_FILENO;
	mini->hd_index = 0;
	mini->status = 0;
	mini->backup_status = 0;
	mini->envlist = make_envlist(envp);
	if (!mini->envlist)
		return (NULL);
	return (mini);
}

static void	process_input(t_minishell *mini)
{
	if (!mini->line)
		ft_clean_exit(mini);
	if (mini->line[0] == '\0')
	{
		free(mini->line);
		mini->line = NULL;
		return ;
	}
	mini->token = ft_lexer(mini->line, mini);
	if (!mini->token)
		return ;
	mini->cmd = build_commands(mini->token,
			count_tokens(mini->token));
	ft_exec_v7(mini);
	status_manager(&mini->status, &mini->backup_status);
	ft_clean(mini, 2);
}

static void	minishell(t_minishell *mini)
{
	setup_signals();
	while (INT_MAX)
	{
		rl_event_hook = handle_mainprompt_signal;
		g_signal_flag |= (1 << 2);
		mini->line = readline("minishell$ ");
		if (observe_sigint(mini->line, 6))
		{
			g_signal_flag &= ~(1 << 1);
			mini->backup_status = 130;
			continue ;
		}
		g_signal_flag &= ~(1 << 2);
		process_input(mini);
	}
	ft_clean_exit(mini);
}

int	main(int argc, char **argv, char **envp)
{
	t_minishell	*mini;

	(void)argc;
	(void)argv;
	mini = init_mini(envp);
	if (!mini)
	{
		print_syscall_error(
			"insufficient memory or system resources", ENOMEM);
		exit(EXIT_FAILURE);
	}
	minishell(mini);
}
