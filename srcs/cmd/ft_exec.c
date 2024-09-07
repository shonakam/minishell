/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 16:44:14 by shonakam          #+#    #+#             */
/*   Updated: 2024/09/08 05:46:28 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"


static void execute_command(t_command *cmd, t_minishell *mini)
{
	char	*path;

	if (cmd->input_fd != STDIN_FILENO)
	{
		if (dup2(cmd->input_fd, STDIN_FILENO) == -1)
			perror("dup2[input_fd]");
		close(cmd->input_fd);
	}
	if (cmd->output_fd != STDOUT_FILENO)
	{
		if (dup2(cmd->output_fd, STDOUT_FILENO) == -1)
			perror("dup2[output_fd]");
		close(cmd->output_fd);
	}
	path = get_bin_path(mini->envlist, cmd->argv[0]);
	if (execve(path, cmd->argv, convert_to_envp(&mini->envlist)) == -1)
	{
		perror("execve");
		// exit(EXIT_FAILURE);
	}
	perror("execute_command: execve");
}

static int	handle_fork(t_command *cmd, t_minishell *mini)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (perror("handle_fork: fork1"), -1);
	if (pid == 0)
		execute_command(cmd, mini);
	return pid;
}

static void	handle_pipe_io(t_command *l, t_command *r)
{
	int	fds[2];
	int	err;

	err = pipe(fds);
	if (err == -1)
	{
		perror("handle_pipe_io: pipe");
		return ;
	}
	l->output_fd = fds[WRITE];
	r->input_fd = fds[READ];
	// printf("W[%d], R[%d]\n", l->output_fd , r->input_fd);
}

int	ft_exec(t_minishell *mini)
{
	t_command	*left;
	t_command	*right;
	int			status;

	left = mini->cmd;
	left->input_fd = STDIN_FILENO;
	while (left)
	{
		if (!left->next)
			left->output_fd = STDOUT_FILENO;
		right = left->next;
		if (right)
			handle_pipe_io(left, right);
		if (handle_fork(left, mini) == -1)
			return (-1);
		if (right)
		{
			close(left->output_fd);
			// close(right->input_fd); //コメントアウトすると動く、なぜ？
		}
		left = right;
	}
	while (waitpid(-1, &status, 0) > 0);
	return (0);
}
