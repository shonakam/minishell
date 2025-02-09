/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_v6.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 08:21:18 by shonakam          #+#    #+#             */
/*   Updated: 2025/02/09 11:03:22 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

/* source[.] is not supported */
static int	resolve_dot(t_command *cmd, t_minishell *mini)
{
	if (!ft_strcmp(cmd->argv[0], "."))
	{
		mini->status = 2;
		ft_putendl_fd("minishell: .: filename argument required", 2);
		ft_putendl_fd(".: usage: . filename [arguments]", 2);
		ft_putendl_fd("\033[31m but not supported\033[0m", 2);
		exit(mini->status);
	}
	return (0);
}

/*
Exit code 0: Command succeeded.
Non-zero exit code: Command failed.
Exit code 128+N: Command terminated by fatal signal N.
	ex: cat -> ctrl + c = 130
Exit code 127: Command not found.
Exit code 126: Command found but not executable.
*/
static void	bin_support(t_command *cmd, int *p, t_minishell *mini)
{
	char	*path;
	char	**envp;
	int		f;

	if (mini->in_fd != STDIN_FILENO)
		redirect_fd(mini->in_fd, STDIN_FILENO);
	if (p && cmd->next)
	{
		close(p[READ]);
		redirect_fd(p[WRITE], STDOUT_FILENO);
	}
	resolve_dot(cmd, mini);
	path = get_bin_path(mini->envlist, cmd->argv[0]);
	f = is_cmd(cmd->argv[0]);
	mini->status = handle_exec_errors(path, p, f);
	if (mini->status != 0)
		exit(mini->status);
	if (f == 0 && !is_last_arg_minishell(cmd->argv[0]))
		exit(resolve_script(cmd, mini));
	envp = convert_to_envp(&mini->envlist);
	execve(path, cmd->argv, envp);
	perror("minishell");
	free(path);
	free_split(envp);
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
}
