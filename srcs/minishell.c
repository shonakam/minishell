/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 15:57:54 by mosh              #+#    #+#             */
/*   Updated: 2024/09/04 21:39:07 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

// void	ft_printenv(t_envlist *list)
// {
// 	printf("----- ENVLIST -----\n");
// 	while (list)
// 	{
// 		printf("Key:%s\n", list->key);
// 		printf("Value: %s\n", list->value);
// 		printf("\n");
// 		list = list->next;
// 	}
// }

void minishell(char **envp)
{
	char		*line;
	t_token 	**tokens;
	t_envlist	*envlist;

	envlist = make_envlist(envp);
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
	(void)argc;
	(void)argv;
	t_envlist *envlist = make_envlist(envp);
	char **r = convert_to_envp(&envlist);

	int len;
	for (len = 0; r[len]; len++);
	for (int i = 0; envp[i]; i++) {
		len--;
		printf("TRY ASSERT:\n>>%s\n>>%s\n", envp[i], r[len]);
		assert(strcmp(envp[i], r[len]) == 0);
	}
	minishell(envp);
	return (0);
}
