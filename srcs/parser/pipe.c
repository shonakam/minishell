/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 22:55:59 by shonakam          #+#    #+#             */
/*   Updated: 2024/09/11 16:21:57 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static void	pipe_loop(int fd, char *delimiter)
{
	char	*line;

	while (1)
	{
		line = readline("pipe> ");
		if (line == NULL)
			break ;
		if ((ft_strlen(line) == ft_strlen(delimiter))
			&& ft_strncmp(line, delimiter, ft_strlen(line)) == 0)
		{
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
}

// tokenの終端がpipeなら繰り返す
t_command	*wait_pipe_cmd(t_command *head)
{
	t_command	*current;
	char		*line;

	current = head;
	while (current)
		current = current->next;
	while (1)
	{
		line = readline("pipe> ");
		if (line == NULL)
			break ;
		
		free(line);
	}
	return (head);
}
