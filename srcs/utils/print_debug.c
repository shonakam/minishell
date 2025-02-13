/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_debug.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 13:29:58 by shonakam          #+#    #+#             */
/*   Updated: 2025/02/13 08:25:21 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	print_tokens(t_token **tokens)
{
	printf("\n\033[1;34m==== START TOKENS ====\033[0m\n");
	if (!tokens)
	{
		printf("\033[1;31mERROR: tokens is NULL\033[0m\n");
		printf("\033[1;34m==== END TOKENS ====\033[0m\n\n");
		return;
	}

	for (size_t i = 0; tokens[i]; i++) {
		printf("\033[1;32mtoken[%ld]:\033[0m '\033[1;33m%s\033[0m'\n", i, tokens[i]->word);
	}

	printf("\033[1;34m==== END TOKENS ====\033[0m\n\n");
}

void	print_commands(t_command *cmd)
{
	printf("\n\033[1;34m==== START COMMANDS ====\033[0m\n");
	if (!cmd)
	{
		printf("\033[1;31mERROR: cmmond is NULL\033[0m\n");
		printf("\033[1;34m==== END COMMANDS ====\033[0m\n\n");
		return;
	}

	t_command *current = cmd;
	for (size_t i = 0; current; i++) {
		for (size_t j = 0; current->argv[j]; j++) {
			printf("\033[1;32mcmd[%ld] argv[%ld]:\033[0m '\033[1;33m%s\033[0m'\n", i, j, current->argv[j]);
		}
		current = current->next;
	}

	printf("\033[1;34m==== END COMMANDS ====\033[0m\n\n");
}

void	print_argv(char **argv)
{
	printf("\n\033[1;34m==== START ARGV ====\033[0m\n");
	if (!argv)
	{
		printf("\033[1;31mERROR: argv is NULL\033[0m\n");
		printf("\033[1;34m==== END ARGV ====\033[0m\n\n");
		return;
	}

	for (size_t i = 0; argv[i]; i++) {
		printf("\033[1;32mcmd[%ld] argv[%ld]:\033[0m '\033[1;33m%s\033[0m'\n", i, 0, argv[i]);
	}

	printf("\033[1;34m==== END ARGV ====\033[0m\n\n");
}
