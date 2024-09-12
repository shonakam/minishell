/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 15:57:54 by mosh              #+#    #+#             */
/*   Updated: 2024/09/12 13:51:41 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static t_minishell	*init_mini(t_minishell *mini, char **envp)
{
	mini->line = NULL;
	mini->token = NULL;
	mini->cmd = NULL;
	mini->envlist = make_envlist(envp);
	if (!mini->envlist)
		return (NULL);
	return (mini);
}

static void	minishell(t_minishell *mini)
{
	if (!mini)
	{
		perror("minishell: insufficient memory or system resources\n");
		exit(EXIT_FAILURE);
	}
	while (INT_MAX)
	{
		mini->line = readline("minishell$ ");
		if (mini->line == NULL)
			break ;
		mini->token = ft_lexer(mini->line); // '|'や'>>'で終わる不完全な文字列は連続して入力を受け続ける
		if (strlen(mini->line) > 0)
			add_history(mini->line);
		if (mini->token == NULL)
			continue ;
		mini->cmd = build_commands(mini->token, count_tokens(mini->token));
		ft_exec_v3(mini);
		ft_clean(mini, 0);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_minishell	mini;

	(void)argc;
	(void)argv;
	minishell(init_mini(&mini, envp));
	return (0);
}
