/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 13:16:02 by shonakam          #+#    #+#             */
/*   Updated: 2025/02/12 22:14:33 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	free_argv(char	**argv)
{
	int	i;

	i = 0;
	if (!argv || !argv[i])
		return ;
	while (argv[i])
		free(argv[i++]);
	free(argv);
}

void	free_commands(t_command *cmd)
{
	t_command	*current;
	t_command	*next;

	current = cmd;
	while (current)
	{
		next = current->next;
		free_heredoc(current);
		if (current && current->argv)
			free_argv(current->argv);
		free(current);
		current = next;
	}
}

int	count_cmd(t_command *cmd)
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
