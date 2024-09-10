/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 16:56:51 by shonakam          #+#    #+#             */
/*   Updated: 2024/09/07 07:40:01 by shonakam         ###   ########.fr       */
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

void	print_ast(t_ast *node, int depth)
{
	if (!node)
		return;
	for (int i = 0; i < depth; i++)
		printf("  ");
	switch (node->type)
	{
		case TOKEN_WORD:
			printf("WORD: ");
			if (node->argv)
			{
				for (int i = 0; node->argv[0]; i++)
					printf("%s\n", node->argv[i]);
			}
			break;
		case METACHAR_PIPE:
			printf("PIPE\n");
			break;
		case METACHAR_OUTPUT_REDIRECT:
			printf("OUTPUT REDIRECT\n");
			break;
		case METACHAR_INPUT_REDIRECT:
			printf("INPUT REDIRECT\n");
			break;
		case METACHAR_APPEND_REDIRECT:
			printf("APPEND REDIRECT\n");
			break;
		default:
			printf("UNKNOWN\n");
			break;
	}
	if (node->left)
		print_ast(node->left, depth + 1);
	if (node->right)
		print_ast(node->right, depth + 1);
}
