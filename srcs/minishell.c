/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 15:57:54 by mosh              #+#    #+#             */
/*   Updated: 2024/09/04 19:03:14 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	ft_printenv(t_envlist *list)
{
	printf("----- ENVLIST -----\n");
	while (list)
	{
		printf("Key:%s\n", list->key);
		printf("Value: %s\n", list->value);
		printf("\n");
		list = list->next;
	}
}

void minishell(char **envp)
{
	char		*line;
	t_token 	**tokens;
	t_envlist	*envlist;

	envlist = make_envlist(envp);
	ft_printenv(envlist);
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

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	for (int i = 0; envp[i]; i++) {
		printf("[%d] %s\n", i, envp[i]);
	}
	minishell(envp);
	return (0);
}
