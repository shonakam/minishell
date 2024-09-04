/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 15:57:54 by mosh              #+#    #+#             */
/*   Updated: 2024/09/04 23:58:51 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void minishell(t_envlist *envlist)
{
	char		*line;
	t_token 	**tokens;

	(void)envlist;
	while (1)
	{
		line = readline("minishell$ ");
		if (line == NULL)
			break;
		if (strlen(line) > 0)
			add_history(line);
		tokens = ft_lexer(line);
		printf(">> %d\n", ft_exec(tokens));
		print_tokens(tokens);
		if (tokens == NULL)
		{
			free(line);
			continue ;
		}
		free(line);
	}
}

#include <assert.h>
int	main(int argc, char **argv, char **envp)
{
	t_envlist	*envlist;
	(void)argc;
	(void)argv;

	envlist = make_envlist(envp);
	minishell(envlist);
	return (0);
}
