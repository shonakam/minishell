/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 15:57:54 by mosh              #+#    #+#             */
/*   Updated: 2024/09/05 04:21:58 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	minishell(t_envlist *envlist)
{
	char		*line;
	t_token 	**tokens;
	t_command	*cmd;

	(void)envlist;
	while (INT_MAX)
	{
		line = readline("minishell$ ");
		if (line == NULL)
			break ;
		if (strlen(line) > 0)
			add_history(line);
		tokens = ft_lexer(line);
		if (tokens == NULL)
			continue ;
		cmd = build_commands(tokens, count_tokens(tokens));
		(void)cmd;
		free_tokens(tokens);
	}
}

#include <assert.h>
void	test_env(t_envlist	*envlist);
int	main(int argc, char **argv, char **envp)
{
	t_envlist	*envlist;
	(void)argc;
	(void)argv;

	envlist = make_envlist(envp);
	// test_env(envlist);
	minishell(envlist);
	return (0);
}
