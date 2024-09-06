/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 16:56:51 by shonakam          #+#    #+#             */
/*   Updated: 2024/09/06 17:38:32 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	print_tokens(t_token **tokens)
{
	if (!tokens)
		return ;
	for (int i=0; tokens[i]; i++) {
		printf("token[%d]: %s\n", i, tokens[i]->word);
	}
}

void	print_commands(t_command *cmd)
{
	if (!cmd)
		return ;
	printf("----- PRINT CMD -----\n");
	for (int i=0; cmd; i++) {
		printf("cmd[%d] argc: %d\n", i, cmd->argc);
		for (int j = 0; cmd->argv && cmd->argv[j]; j++)
			printf("cmd[%d] argv[%d]: %s\n", i, j, cmd->argv[j]);
		printf("cmd[%d] append_fd: %d\n", i, cmd->append_fd);
		printf("cmd[%d] imput_fd: %d\n", i, cmd->input_fd);
		printf("cmd[%d] output_fd: %d\n", i, cmd->output_fd);
		printf("\n");
		cmd = cmd->next;
	}
	printf("---------------------\n");
}

void	print_paths(t_token **tokens)
{
	if (!tokens)
		return ;
	for (int i=0; tokens[i]; i++) {
		printf("token[%d]: %s\n", i, tokens[i]->word);
	}
}

