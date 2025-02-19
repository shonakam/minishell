/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_bin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 17:38:06 by shonakam          #+#    #+#             */
/*   Updated: 2025/02/19 23:12:07 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static int	handle_exec_err(
	const char *cmd, const char *path, t_minishell *mini)
{
	struct stat	sb;

	if (stat(path, &sb) == -1)
		return (handle_file_not_found(cmd, path, mini));
	else
		return (handle_file_type_error(cmd, path, sb, mini));
}

static char	*set_path(t_command *cmd, t_minishell *mini)
{
	char	*path;

	if (!cmd->argv || !cmd->argv[0])
	{
		path = ft_strdup("");
		if (!path)
			print_syscall_error("malloc: set_path", ENOMEM);
		return (path);
	}
	if (cmd->argv[0][0] == '/')
		path = ft_strdup(cmd->argv[0]);
	else if (ft_strlen(cmd->argv[0]) > 1
		&& cmd->argv[0][0] == '.' && cmd->argv[0][1] == '/')
		path = ft_strdup(cmd->argv[0]);
	else
		path = get_bin_path(mini->envlist, cmd->argv[0]);
	if (!path)
		print_syscall_error("malloc: set_path", ENOMEM);
	return (path);
}

static void	*try_exec_bin(
		t_rdir *i, t_command *cmd, int *pipe, t_minishell *mini)
{
	char	*path;
	char	**envp;

	fd_navigate(i, cmd, pipe, mini);
	path = set_path(cmd, mini);
	if (handle_exec_err(cmd->argv[0], path, mini))
		return (free(path), free_info(i), ft_clean_child(mini), NULL);
	envp = convert_to_envp(&mini->envlist);
	execve(path, cmd->argv, envp);
	print_syscall_error("execve: try_exec_bin", 0);
	mini->status = 127;
	return (free(path), free_split(envp), ft_clean_child(mini), NULL);
}

void	exec_bin(t_rdir *i, t_command *cmd, int *p, t_minishell *mini)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		try_exec_bin(i, cmd, p, mini);
	}
	else
	{
		if (cmd->next)
			close(p[WRITE]);
		if (mini->in_fd != 0)
			close(mini->in_fd);
	}
}
