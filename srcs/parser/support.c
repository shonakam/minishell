/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   support.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 03:38:04 by shonakam          #+#    #+#             */
/*   Updated: 2024/09/07 03:30:09 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

t_command	*get_current_cmd(t_command *cmd, int depth)
{
	t_command	*current;
	int			i;

	current = cmd;
	i = 0;
	while (!current && i++ < depth)
		current = current->next;
	return (current);
}

int		count_cmd(t_command *cmd)
{
	t_command	*current;
	int			i;

	current = cmd;
	i = 0;
	while (current)
	{
		i += 1;
		current = current->next;
	}
	return (i);
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
			perror("cpy_args: strdup");
			while (i > 0)
				free(a[--i]);
			free(a);
			return;
		}
		i++;
	}
	i = 0;
	while (cmd->argv[i])
		free(cmd->argv[i++]);
	free(cmd->argv);
}

void	free_close_commands(t_command *cmd)
{
	t_command	*current;
	t_command	*next;
	int			i;

	current = cmd;
	while (current)
	{
		next = current->next;
		if (current->argv)
		{
			i = 0;
			while (current->argv[i])
				free(current->argv[i++]);
			free(current->argv);
		}
		if (current->input_fd != -1)
			close(current->input_fd);
		if (current->output_fd != -1)
			close(current->output_fd);
		if (current->append_fd != -1)
			close(current->append_fd);
		free(current);
		current = next;
	}
}
