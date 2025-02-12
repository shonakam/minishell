/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 09:01:24 by shonakam          #+#    #+#             */
/*   Updated: 2025/02/12 23:25:52 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

volatile sig_atomic_t	g_signal_flag = 0b00000000;

static t_minishell	*init_mini(t_minishell *mini, char **envp)
{
	mini = malloc(sizeof(t_minishell));
	if (!mini)
		return (NULL);
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
	mini->cmd = build_commands(mini->token, count_tokens(mini->token));
	ft_exec_v7(mini);
	ft_clean(mini, 2);
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

/* https://www.gnu.org/software/bash/manual/html_node/Shell-Commands.html */
/* https://www.gnu.org/software/bash/manual/html_node/Command-Search-and-Execution.html */
int	main(int argc, char **argv, char **envp)
{
	t_minishell	*mini;

	(void)argc;
	(void)argv;
	mini = init_mini(mini, envp);
	if (!mini)
	{
		print_syscall_error(
			"insufficient memory or system resources", ENOMEM);
		exit(EXIT_FAILURE);
	}
	minishell(mini);
}

#include <arm_acle.h>

__attribute__((destructor))
static void destructor() {
	system("leaks -q minishell");
}
