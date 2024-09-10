/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_v3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 00:01:53 by shonakam          #+#    #+#             */
/*   Updated: 2024/09/11 00:36:10 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

typedef struct	s_pipe {
	int	read_end;
	int	write_end;
}				t_pipe;

void exec_command(char *cmd, t_pipe *i, t_pipe *o, t_minishell *mini)
{
	pid_t	pid;
	char	*path;

	pid = fork();
	if (pid == -1)
		perror("fork");
	if (pid == 0)
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
		path = get_bin_path(mini->envlist, cmd);
		execve(path, mini->cmd->argv, NULL);
		perror("execlp");
	}
}

void create_pipe(int pipe_fd[2])
{
	int	err;

	err = pipe(pipe_fd);
	if (err == -1)
	{
		perror("pipe");
	}
}

// void	set_pipe()
// {
// 		if (cmd->next != NULL)
// 		{
// 			create_pipe(&pipe_out);
// 			out_pipe_ptr = &pipe_out;  // Set the output pipe pointer to pipe_out
// 		}
// 		else
// 		{
// 			out_pipe_ptr = NULL;  // No next command, so no output pipe needed
// 		}

// 		// If this is the first command, no input pipe, otherwise set to pipe_in
// 		if (cmd == mini->cmd)
// 		{
// 			in_pipe_ptr = NULL;  // First command has no input pipe
// 		}
// 		else
// 		{
// 			in_pipe_ptr = &pipe_in;  // Use pipe_in for subsequent commands
// 		}
// }

void	ft_exec_v3(t_minishell *mini)
{
	t_pipe	pipe_in = {-1, -1};
	t_pipe	pipe_out = {-1, -1};
	t_command *cmd = mini->cmd;

	while (cmd != NULL)
	{
		if (cmd->next != NULL)
			create_pipe(&pipe_out);
		exec_command(cmd->argv[0], 
			(cmd == mini->cmd ? NULL : &pipe_in),  // Use pipe_in if not the first command
			(cmd->next != NULL ? &pipe_out : NULL), mini);  // Use pipe_out if there’s a next command
		// Close old pipe_in fds
		if (pipe_in.read_end != -1)
		{
			close(pipe_in.read_end);
			close(pipe_in.write_end);
		}
		// Update pipe_in for the next iteration
		pipe_in = pipe_out;
		cmd = cmd->next;
	}
	// Close remaining pipe fds if they exist
	if (pipe_in.read_end != -1)
	{
		close(pipe_in.read_end);
		close(pipe_in.write_end);
	}
	while (waitpid(-1, &mini->status, 0) > 0)
		;
	printf(">> END EXEC\n");
}