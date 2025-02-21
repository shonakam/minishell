/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_builder.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 00:52:47 by mosh              #+#    #+#             */
/*   Updated: 2025/02/19 14:15:00 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static t_command	*create_command(int track)
{
	t_command	*cmd;

	cmd = (t_command *)malloc(sizeof(t_command));
	if (!cmd)
		return (print_syscall_error("create_command: malloc", ENOMEM), NULL);
	cmd->track = track;
	cmd->argv = NULL;
	cmd->argc = 0;
	cmd->hd_list = NULL;
	cmd->next = NULL;
	return (cmd);
}

/* NEW SIZE = CAURRENT + NEXT + NULL */
static char	**resize_args(t_command *cmd)
{
	char	**args;

	args = malloc(sizeof(char *) * (cmd->argc + 2));
	if (!args)
		return (print_syscall_error("malloc: resize_args", ENOMEM), NULL);
	if (cmd->argv)
	{
		cpy_args(cmd, args);
		free(cmd->argv);
	}
	return (args);
}

static t_command	*set_argument(t_command *cmd, char *token)
{
	char	**args;

	args = resize_args(cmd);
	if (!args)
		return (print_syscall_error("malloc: set_argument", ENOMEM), NULL);
	args[cmd->argc] = ft_strdup(token);
	if (!args[cmd->argc])
		return (print_syscall_error("malloc: set_argument", ENOMEM), NULL);
	cmd->argc++;
	cmd->argv = args;
	args[cmd->argc] = NULL;
	return (cmd);
}

t_command	*build_commands(t_token **tokens, int count)
{
	t_command	*head;
	t_command	*current;
	int			i;

	head = create_command(0);
	current = head;
	i = 0;
	while (i < count && tokens[i])
	{
		if (tokens[i]->type == METACHAR_PIPE)
		{
			if (!(tokens[++i]))
				return (head);
			current->next = create_command(i);
			current = current->next;
		}
		else
		{
			current = set_argument(current, tokens[i]->word);
			if (!current)
				return (head);
			i++;
		}
	}
	return (head);
}
