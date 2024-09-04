/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 15:57:54 by mosh              #+#    #+#             */
/*   Updated: 2024/09/04 16:18:53 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void minishell(char **envp)
{
	char		*line;
	t_token 	**tokens;

	make_envlist(envp);
	(void)envp;
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
