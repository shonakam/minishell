/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 13:16:02 by shonakam          #+#    #+#             */
/*   Updated: 2025/02/19 14:15:15 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	free_argv(char	**argv)
{
	int	i;

	i = 0;
	if (!argv)
		return ;
	while (argv[i])
		free(argv[i++]);
	free(argv);
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
			print_syscall_error("ft_strdup: cpy_args", 0);
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
