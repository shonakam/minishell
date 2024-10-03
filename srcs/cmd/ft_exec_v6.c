/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_v6.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 08:21:18 by shonakam          #+#    #+#             */
/*   Updated: 2024/10/03 12:13:54 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

/*
Exit code 0: Command succeeded.
Non-zero exit code: Command failed.
Exit code 128+N: Command terminated by fatal signal N.
	ex: cat -> ctrl + c = 130
Exit code 127: Command not found.
Exit code 126: Command found but not executable.
*/
static  void	bin_support(t_command *cmd, int *p, t_minishell *mini)
{
	char	*path;

	if (mini->in_fd != STDIN_FILENO)
		redirect_fd(mini->in_fd, STDIN_FILENO);
	if (p && cmd->next)
	{
		close(p[READ]);
		redirect_fd(p[WRITE], STDOUT_FILENO);
	}
	path = get_bin_path(mini->envlist, cmd->argv[0]);
	mini->status = handle_exec_errors(path, p, is_cmd(cmd->argv[0]));
	if (mini->status != 0)
		exit(mini->status);
	execve(path, cmd->argv, convert_to_envp(&mini->envlist));
	perror("minishell");
	exit(EXIT_FAILURE);
}

void	exec_bin(t_command *cmd, int *p, t_minishell *mini)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
		bin_support(cmd, p, mini);
	else
	{
		if (cmd->next)
			close(p[WRITE]);
		if (mini->in_fd != 0)
			close(mini->in_fd);
	}
	g_signal_flag = (sig_atomic_t)pid;
	mini->status = parse_exit_status(mini->status);
	g_signal_flag = 0b00000000;
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
		if (info->rdir_i == INT_MIN)
		{
			mini->status = 1;
			free(info);
			break ;
		}
		else
			exec_handler(cmd, mini, p, info);
		free(info);
		cmd = cmd->next;
	}
	while (waitpid(-1, &mini->status, 0) > 0)
		;
	mini->status = parse_exit_status(mini->status);
	printf("m:status=%d\n", mini->status);
}
