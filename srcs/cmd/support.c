/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   support.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 21:39:37 by shonakam          #+#    #+#             */
/*   Updated: 2024/09/16 03:49:22 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

// エラー時にプロセスを終了
// old_fdはもう使わないので閉じる
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

int		is_executable(const char *path)
{
	if (access(path, F_OK) != 0)
		return (0);
	if (access(path, X_OK) != 0)
		return (0);
	return (1);
}

void free_heredoc(t_command *cmd)
{
	t_heredoc *current;
	t_heredoc *next;

	current = cmd->hd_list;
	while (current)
	{
		next = current->next;
		free(current->filename);
		free(current);
		current = next;
	}
}

// void	initialize_pipes(t_pipe *pipe_in, t_pipe *pipe_out)
// {
// 	if (pipe_in != NULL)
// 	{
// 		pipe_in->read_end = -1;
// 		pipe_in->write_end = -1;
// 	}
// 	if (pipe_out != NULL)
// 	{
// 		pipe_out->read_end = -1;
// 		pipe_out->write_end = -1;
// 	}
// }

// void close_pipe(t_pipe *pipe)
// {
// 	if (pipe->read_end != -1)
// 	{
// 		close(pipe->read_end);
// 		pipe->read_end = -1; // Mark as closed
// 	}
// 	if (pipe->write_end != -1)
// 	{
// 		close(pipe->write_end);
// 		pipe->write_end = -1; // Mark as closed
// 	}
// }