/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   support.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 03:38:04 by shonakam          #+#    #+#             */
/*   Updated: 2024/09/06 17:42:03 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

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
	int			i;

	current = cmd;
	while (current)
	{
		if (cmd->argv)
		{
			i = 0;
			while (cmd->argv[i])
				free(cmd->argv[i++]);
			free(cmd->argv);
		}

		if (cmd->input_fd != -1)
			close(cmd->input_fd);
		if (cmd->output_fd != -1)
			close(cmd->output_fd);
		if (cmd->append_fd != -1)
			close(cmd->append_fd);
		free(cmd);
		current = current->next;
	}
}
