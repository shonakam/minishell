/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_v5.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 06:20:22 by shonakam          #+#    #+#             */
/*   Updated: 2024/09/19 09:08:06 by shonakam         ###   ########.fr       */
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
	// mini->status = 126;
	free(path);
	exit(EXIT_FAILURE);
}

static void	exec_bin(t_command *cmd, int *p, t_minishell *mini)
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

static void	exec_pattern(t_command *cmd, int *p, t_minishell *mini)
{
	if (is_builtin(cmd))
	{
		if (cmd->next)
		{
			builtin_runner(cmd, p[WRITE], mini->envlist);
			close(p[WRITE]);
			mini->in_fd = p[READ]; 
		}
		else
			mini->status = builtin_runner(cmd, 0, mini->envlist);
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

static	int	exec_handler(t_command	*c, t_minishell *m, int *p, t_rdir *info)
{
	int		i;
	char 	*tmp;

	if (c->next)
			handle_pipe(p, 0);
	if (handle_heredoc(c, &m->hd_index, m->status, m->envlist) == 1)
	{
		m->status = 0;
		if (c->next)
			handle_pipe(p, 1);
		return (1);
	}
	if (c->hd_list)
		rebuild_args(c);
	i = 0;
	while (c->argv[i])
	{
		tmp = expand_variables(c->argv[i], m->status, m->envlist);
		free(c->argv[i]);
		c->argv[i++] = remove_quotes(tmp);
	}
	set_bkp_fd(info);
	apply_redirects(info);
	return (exec_pattern(c, p, m), restore_io(info), 0);
}



/*
-- manage heredoc
-- expand args
-- redirect | bin / builtins
-- export TMP=s1 > cat "$TMP" ok
-- [cd,export,unset,exit] directly modify the shell’s state or environment
-- set_redirect[fd] -> (set_pipe[fd]) -> exec[builtin/bin] -> restore[fd]
*/
void	ft_exec_v5(t_minishell *mini)
{
	t_command	*cmd;
	int			p[2];
	t_rdir		*info;

	cmd = mini->cmd;
	while (cmd)
	{
		info = init_redirect();
		if (exec_handler(cmd, mini, p, info))
		{
			if (info)
				free(info);
			cmd = cmd->next;
			continue ;
		}
		if (info)
			free(info);
		cmd = cmd->next;
	}
	while (waitpid(-1, &mini->status, 0) > 0)
		;
}
