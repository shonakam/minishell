/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   support.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 21:39:37 by shonakam          #+#    #+#             */
/*   Updated: 2025/02/09 04:29:45 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	redirect_fd(int old, int new)
{
	if (old != new)
	{
		if (dup2(old, new) == -1)
		{
			perror("dup2 failed");
			exit(EXIT_FAILURE);
		}
		close(old);
	}
}

int	is_executable(const char *path)
{
	if (access(path, F_OK) != 0)
		return (0);
	if (access(path, X_OK) != 0)
		return (0);
	return (1);
}

void	free_heredoc(t_command *cmd)
{
	t_heredoc	*current;
	t_heredoc	*next;

	if (!cmd)
		return ;
	current = cmd->hd_list;
	while (current)
	{
		next = current->next;
		free(current->filename);
		free(current);
		current = next;
	}
}

void	handle_pipe(int *p, int f)
{
	if (f == 0)
	{
		if (pipe(p) == -1)
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		}
	}
	else if (f == 1)
	{
		close(p[READ]);
		close(p[WRITE]);
	}
}

int	is_cmd(char *cmd)
{
	if (!ft_strchr(cmd, '/'))
		return (1);
	return (0);
}
