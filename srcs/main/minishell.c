/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 15:57:54 by mosh              #+#    #+#             */
/*   Updated: 2024/09/21 00:00:28 by shonakam         ###   ########.fr       */
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

void	print_tokens(t_token **tokens)
{
	if (!tokens)
		return ;
	for (int i=0; tokens[i]; i++) {
		printf("token[%d]: %s\n", i, tokens[i]->word);
	}
}

static void	minishell(t_minishell *mini)
{
	// setup_signals();
	char *l = "ls | cat";
	while (INT_MAX)
	{
		mini->line = l;
		// mini->line = readline("minishell$ ");
		// if (mini->line == NULL)
		// 	break ;
		// if (g_signal_flag & (1 << 0))
		// {
		// 	printf("\033[31mBREAKPOINT\033[0m\n");
		// 	g_signal_flag &= ~(1 << 0);
		// 	continue ;
		// }
		mini->token = ft_lexer(mini->line);
		if (mini->token == NULL)
			continue ;
		mini->cmd = build_commands(mini->token, count_tokens(mini->token));
		print_tokens(mini->token);
		ft_exec_v6(mini);
		free_commands(mini->cmd);
		free_tokens(mini->token);
		exit(0);
		// ft_clean(mini, 0);
		ft_clean_exit(mini);
	}
	printf("\033[31mBREAKPOINT\033[0m\n");
	// ft_clean_exit(mini);
}

int	main(int argc, char **argv, char **envp)
{
	t_minishell	*mini;

	(void)argc;
	(void)argv;
	mini = init_mini(mini, envp);
	if (!mini)
	{
		perror("minishell: insufficient memory or system resources\n");
		exit(EXIT_FAILURE);
	}
	minishell(mini);
	return (0);
}

__attribute__((destructor))
static void destructor() {
	system("leaks -q minishell");
}
