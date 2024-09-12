/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   support.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 21:39:37 by shonakam          #+#    #+#             */
/*   Updated: 2024/09/11 15:27:06 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

// void	dup_descriptor(t_command *cmd)
// {
// 	if (cmd->input_fd != STDIN_FILENO)
// 	{
// 		if (dup2(cmd->input_fd, STDIN_FILENO) == -1)
// 			perror("dup_descriptor: dup2[input_fd]");
// 		close(cmd->input_fd);
// 	}
// 	if (cmd->output_fd != STDOUT_FILENO)
// 	{
// 		if (dup2(cmd->output_fd, STDOUT_FILENO) == -1)
// 			perror("dup_descriptor: dup2[output_fd]");
// 		close(cmd->output_fd);
// 	}
// }

void	dup_handler(t_pipe *i, t_pipe *o)
{
	if (i != NULL)
	{
		close(i->write_end);				// 入力パイプの書き込み側を閉じる
		dup2(i->read_end, STDIN_FILENO);	// 標準入力をパイプの読み取り側にリダイレクト
		close(i->read_end);					// リダイレクト後にパイプの読み取り側を閉じる
	}
	if (o != NULL)
	{
		close(o->read_end);					// 出力パイプの読み取り側を閉じる
		dup2(o->write_end, STDOUT_FILENO);	// 標準出力をパイプの書き込み側にリダイレクト
		close(o->write_end);				// リダイレクト後にパイプの書き込み側を閉じる
	}
}

int		count_pipe(t_token **tokens)
{
	int	i;

	i = 0;
	while (*tokens)
	{
		if ((*tokens)->type == METACHAR_PIPE)
			i++;
		tokens++;
	}
	return (i);
}

int		is_executable(const char *path)
{
	if (access(path, F_OK) != 0)
		return (0);
	if (access(path, X_OK) != 0)
		return (0);
	return (1);
}

void	initialize_pipes(t_pipe *pipe_in, t_pipe *pipe_out)
{
	if (pipe_in != NULL)
	{
		pipe_in->read_end = -1;
		pipe_in->write_end = -1;
	}
	if (pipe_out != NULL)
	{
		pipe_out->read_end = -1;
		pipe_out->write_end = -1;
	}
}

void close_pipe(t_pipe *pipe)
{
	if (pipe->read_end != -1)
	{
		close(pipe->read_end);
		pipe->read_end = -1; // Mark as closed
	}
	if (pipe->write_end != -1)
	{
		close(pipe->write_end);
		pipe->write_end = -1; // Mark as closed
	}
}