/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_v5.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 06:20:22 by shonakam          #+#    #+#             */
/*   Updated: 2024/09/14 21:02:01 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static void	exec_bin(t_command *cmd, int *p, t_minishell *mini)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		if (mini->in_fd != STDIN_FILENO)
			redirect_fd(mini->in_fd, STDIN_FILENO);
		if (p && cmd->next)
		{
			close(p[READ]);
			redirect_fd(p[WRITE], STDOUT_FILENO);
		}
		execve(get_bin_path(mini->envlist, cmd->argv[0]),
			cmd->argv, convert_to_envp(&mini->envlist));
		perror("execve");
		exit(EXIT_FAILURE);
	}
	else
	{
		if (cmd->next)
			close(p[WRITE]);
		if (mini->in_fd != 0)
			close(mini->in_fd);
	}
}

static void	exec_pattern(t_command *cmd, int *p, t_minishell *mini)
{
	if (is_builtin(cmd))
	{
		if (cmd->next)
		{
			builtin_runner(cmd, p[WRITE]);
			close(p[WRITE]);
			mini->in_fd = p[READ]; 
		}
		else
			builtin_runner(cmd, 0);
	}
	else
	{
		if (cmd->next)
		{
			exec_bin(cmd, p, mini);
			mini->in_fd = p[READ];
		}
		else
			exec_bin(cmd, NULL, mini);
	}
}

void	ft_exec_v5(t_minishell *mini)
{
	t_command	*cmd;
	int			p[2];

	cmd = mini->cmd;
	while (cmd)
	{
		if (cmd->next)
		{
			if (pipe(p) == -1)
			{
				perror("pipe");
				// free
				exit(EXIT_FAILURE);
			}
		}
		exec_pattern(cmd, p, mini);
		cmd = cmd->next;
	}
	while (waitpid(-1, &mini->status, 0) > 0)
		;
}