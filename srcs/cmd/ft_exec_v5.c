/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_v5.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 06:20:22 by shonakam          #+#    #+#             */
/*   Updated: 2024/09/14 20:39:37 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static void	exec_bin(t_command *cmd, int in_fd, int *p, t_minishell *mini)
{
	char	*path;
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		if (in_fd != 0)
		{
			dup2(in_fd, STDIN_FILENO);
			close(in_fd);
		}
		if (cmd->next)
		{
			close(p[READ]);
			dup2(p[WRITE], STDOUT_FILENO);
			close(p[WRITE]);
		}
		path = get_bin_path(mini->envlist, cmd->argv[0]);
		execve(path, cmd->argv, convert_to_envp(&mini->envlist));
		perror("execve");
		free(path);
		exit(EXIT_FAILURE);
	}
	else
	{
		if (cmd->next)
			close(p[WRITE]);
		if (in_fd != 0)
			close(in_fd);
	}
}

static void create_pipe(int *p)
{
	if (pipe(p) == -1)
	{
		perror("pipe");
		// free
		exit(EXIT_FAILURE);
	}
}

static void	exec_pattern(t_command *cmd, int *p, t_minishell *mini)
{
	if (is_builtin(cmd))
	{
		if (cmd->next)
		{
			builtin_runner(cmd, p[WRITE]);
			close(p[WRITE]); // 書き込みを閉じる
			mini->in_fd = p[READ]; 
		}
		else
			builtin_runner(cmd, 0);
	}
	else
	{
		exec_bin(cmd, mini->in_fd, p, mini);
		mini->in_fd = p[READ];
	}
}

void	ft_exec_v5(t_minishell *mini)
{
	t_command	*cmd;
	int			p[2];
	int			in_fd;

	in_fd = 0;
	cmd = mini->cmd;
	while (cmd)
	{
		if (cmd->next)
			create_pipe(p);
		if (is_builtin(cmd))
		{
			if (cmd->next)
			{
				builtin_runner(cmd, p[WRITE]);
				close(p[WRITE]); // 書き込みを閉じる
				in_fd = p[READ]; 
			}
			else
				builtin_runner(cmd, 0);
		}
		else
		{
			exec_bin(cmd, in_fd, p, mini);
			in_fd = p[READ];
		}
		cmd = cmd->next;
	}
	while (waitpid(-1, &mini->status, 0) > 0)
		;
}
