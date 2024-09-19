/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_v6.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 08:21:18 by shonakam          #+#    #+#             */
/*   Updated: 2024/09/19 16:41:23 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static void	bin_support(t_command *cmd, int *p, t_minishell *mini)
{
	char *path;

	if (mini->in_fd != STDIN_FILENO)
		redirect_fd(mini->in_fd, STDIN_FILENO);
	if (p && cmd->next)
	{
		close(p[READ]);
		redirect_fd(p[WRITE], STDOUT_FILENO);
	}
	path = get_bin_path(mini->envlist, cmd->argv[0]);
	if (access(path, F_OK) == -1)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd("command not found: ", STDERR_FILENO);
		ft_putendl_fd(cmd->argv[0], STDERR_FILENO);
		mini->status = 1;
		return ;
	}
	execve(path, cmd->argv, convert_to_envp(&mini->envlist));
	perror("minishell");
	free(path);
	exit(EXIT_FAILURE);
}

void	exec_bin(t_command *cmd, int *p, t_minishell *mini)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		bin_support(cmd, p, mini);
	}
	else
	{
		if (cmd->next)
			close(p[WRITE]);
		if (mini->in_fd != 0)
			close(mini->in_fd);
	}
} 

/*
-- manage heredoc
-- expand args
-- redirect | bin / builtins
-- export TMP=s1 > cat "$TMP" ok
-- [cd,export,unset,exit] directly modify the shell’s state or environment
-- set_redirect[fd] -> (set_pipe[fd]) -> exec[builtin/bin] -> restore[fd]
-- サポートなし: cat < s2 | export
*/
void	ft_exec_v6(t_minishell *mini)
{
	t_command	*cmd;
	int			p[2];
	t_rdir		*info;

	cmd = mini->cmd;
	while (cmd)
	{
		info = init_redirect();
		parse_redirects(cmd, info);
		if (exec_handler(cmd, mini, p, info))
		{
			free(info);
			cmd = cmd->next;
			continue ;
		}
		free(info);
		cmd = cmd->next;
	}
	while (waitpid(-1, &mini->status, 0) > 0)
		;
	// sleep(5);
	// printf("\033[31mBREAKPOINT\033[0m\n");
}