/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_builder.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 00:52:47 by mosh              #+#    #+#             */
/*   Updated: 2025/02/12 22:17:02 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

t_command	*create_command(void)
{
	t_command *cmd = (t_command *)malloc(sizeof(t_command));
	if (!cmd)
		return (print_syscall_error("create_command: malloc", ENOMEM), NULL);
	cmd->argv = NULL;
	cmd->argc = 1;
	cmd->hd_list = NULL;
	cmd->next = NULL;
	return (cmd);
}

void	cpy_args(t_command *cmd, char **a)
{
	int	i;

	i = 0;
	while (cmd->argv[i])
	{
		a[i] = ft_strdup(cmd->argv[i]);
		if (!a[i])
		{
			print_syscall_error("strdup: cpy_args", 0);
			while (i > 0)
				free(a[--i]);
			free(a);
			return ;
		}
		i++;
	}
	i = 0;
	while (cmd->argv[i])
		free(cmd->argv[i++]);
}

static char	**resize_args(t_command *cmd)
{
	char	**args;

	args = malloc(sizeof(char *) * (cmd->argc + 1));
	if (!args)
		return (print_syscall_error("malloc: resize_args", ENOMEM), NULL);
	if (cmd->argv)
	{
		cpy_args(cmd, args);
		free(cmd->argv);
	}
	return (args);
}

t_command	*set_argument(t_command *cmd, char *token)
{
	char	**args;

	args = resize_args(cmd);
	if (!args)
		return (print_syscall_error("malloc: set_argument", ENOMEM), NULL);
	args[cmd->argc - 1] = ft_strdup(token);
	if (!args[cmd->argc - 1])
		return (print_syscall_error("malloc: set_argument", ENOMEM), NULL);
	// printf("HELLO\n");
	args[cmd->argc] = NULL;
	cmd->argv = args;
	cmd->argc++;
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
			if (!(tokens[++i]))
				return (head);
			current->next = create_command();
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
