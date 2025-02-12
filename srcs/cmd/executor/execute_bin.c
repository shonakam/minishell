/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_bin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 17:38:06 by shonakam          #+#    #+#             */
/*   Updated: 2025/02/13 05:13:25 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

/* check file or dir -> check permission */
static int	handle_exec_err(
	const char *cmd, const char *path, t_minishell *mini)
{
	struct stat	sb;

	if (stat(path, &sb) == -1)
		print_exec_error(cmd, ": No such file or directory", 127, mini);
	else
	{
		if (S_ISDIR(sb.st_mode))
			print_exec_error(cmd, ": Is a directory", 126, mini);
		else if (S_ISREG(sb.st_mode))
			if (access(path, X_OK) == -1)
				print_exec_error(cmd, ": Permission denied", 126, mini);
			else
				return (0);
		else if (S_ISLNK(sb.st_mode))
			print_exec_error(cmd, ": Unknown file type", 127, mini);
		else
			print_exec_error(cmd, ": Not a directory", 127, mini);
	}
	return (1);
}

static char *set_path(t_command *cmd, t_minishell *mini)
{
	char	*path;

	if (cmd->argv[0][0] == '/')
		path = ft_strdup(cmd->argv[0]);
	else if (ft_strlen(cmd->argv[0]) > 1
		&& cmd->argv[0][0] == '.'
		&& cmd->argv[0][1] == '/')
		path = ft_strdup(cmd->argv[0]);
	else
		path = get_bin_path(mini->envlist, cmd->argv[0]);
	return (path);
}

static void	*try_exec_bin(t_command *cmd, int *pipe, t_minishell *mini)
{
	char	*path;
	char	**envp;

	if (mini->in_fd != STDIN_FILENO)
		redirect_fd(mini->in_fd, STDIN_FILENO);
	if (pipe && cmd->next)
	{
		close(pipe[READ]);
		redirect_fd(pipe[WRITE], STDOUT_FILENO);
	}
	path = set_path(cmd, mini);
	if (handle_exec_err(cmd->argv[0], path, mini))
		return (free(path), NULL);
	envp = convert_to_envp(&mini->envlist);
	execve(path, cmd->argv, envp);
	print_syscall_error("try_exec_bin: execve", 0);
	return (free(path), free_split(envp), exit(EXIT_FAILURE), NULL);
}

void	exec_bin(t_command *cmd, int *p, t_minishell *mini)
{
	pid_t			pid;

	pid = fork();
	if (pid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		try_exec_bin(cmd, p, mini);
	}
	else
	{
		if (cmd->next)
			close(p[WRITE]);
		if (mini->in_fd != 0)
			close(mini->in_fd);
	}
	g_signal_flag = 0b00000000;
}
