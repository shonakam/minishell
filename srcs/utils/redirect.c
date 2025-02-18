/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 17:35:07 by shonakam          #+#    #+#             */
/*   Updated: 2025/02/12 21:13:23 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	handle_pipe(t_command *cmd, int *p, int flag)
{
	if (cmd->next)
	{
		if (flag == 0)
		{
			if (pipe(p) == -1)
			{
				print_syscall_error("pipe: handle_pipe", 0);
				exit(EXIT_FAILURE);
			}
		}
		else if (flag == 1)
		{
			close(p[READ]);
			close(p[WRITE]);
		}
	}
}

int	get_redirect_mode(char *arg)
{
	int	mode;

	if (ft_strcmp(arg, ">>") == 0)
		mode = O_CREAT | O_WRONLY | O_TRUNC;
	else if (ft_strcmp(arg, ">") == 0)
		mode = O_CREAT | O_WRONLY | O_APPEND;
	else if (ft_strcmp(arg, "<") == 0)
		mode = O_RDONLY;
	else
		mode = -1;
	return (mode);
}

void	redirect_fd(int old, int new)
{
	if (old != new)
	{
		if (dup2(old, new) == -1)
		{
			print_syscall_error("dup2: redirect_fd", 0);
			exit(EXIT_FAILURE);
		}
		close(old);
	}
}
