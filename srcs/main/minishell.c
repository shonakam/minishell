/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 15:57:54 by mosh              #+#    #+#             */
/*   Updated: 2025/02/09 06:38:22 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

volatile sig_atomic_t	g_signal_flag = 0b00000000;

static t_minishell	*init_mini(t_minishell *mini, char **envp)
{
	mini->line = NULL;
	mini->token = NULL;
	mini->cmd = NULL;
	mini->in_fd = STDIN_FILENO;
	mini->hd_index = 0;
	mini->status = 0;
	mini->envlist = make_envlist(envp);
	if (!mini->envlist)
		return (NULL);
	return (mini);
}

static void	process_input(t_minishell *mini)
{
	if (mini->line == NULL)
		ft_clean_exit(mini);
	if (mini->line[0] == '\0')
	{
		free(mini->line);
		mini->line = NULL;
		return ;
	}
	mini->token = ft_lexer(mini->line);
	if (mini->token == NULL)
		return ;
	mini->cmd = build_commands(mini->token, count_tokens(mini->token));
	ft_exec_v6(mini);
	ft_clean(mini, 0);
}

static void	minishell(t_minishell *mini)
{
	setup_signals();
	while (INT_MAX)
	{
		g_signal_flag |= (1 << 2);
		mini->line = readline("minishell$ ");
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
	mini = malloc(sizeof(t_minishell));
	if (!mini)
	{
		perror("minishell: lack of resources\n");
		exit(EXIT_FAILURE);
	}
	mini = init_mini(mini, envp);
	if (!mini)
	{
		perror("minishell: insufficient memory or system resources\n");
		exit(EXIT_FAILURE);
	}
	minishell(mini);
}
