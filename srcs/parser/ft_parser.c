/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 00:52:47 by mosh              #+#    #+#             */
/*   Updated: 2024/09/15 22:05:21 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

// コマンド構造体を作成する関数
t_command	*create_command(void)
{
	t_command *cmd;
	
	cmd = (t_command *)malloc(sizeof(t_command));
	if (!cmd) {
		perror("create_command: malloc");
		exit(EXIT_FAILURE);
	}
	cmd->argv = NULL;
	cmd->argc = 0;
	cmd->hd_list = NULL;
	cmd->next = NULL;
	return (cmd);
}

t_command	*build_commands(t_token **tokens, int count)
{
	t_command	*head;
	t_command	*current;
	int			i;

	head = create_command();
	current = head;
	i = 0;
	while (i < count && tokens[i])
	{
		if (tokens[i]->type == METACHAR_PIPE)
		{
			if (!tokens[++i])
				return (head); // pipe待機
			current->next = create_command();
			current = current->next;
		}
		else
			current = set_argument(current, tokens[i++]->word);
	}
	return (head);
}
