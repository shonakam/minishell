/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_v6.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 08:21:18 by shonakam          #+#    #+#             */
/*   Updated: 2024/09/19 09:11:39 by shonakam         ###   ########.fr       */
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

static int	handle_redirect_and_pipe(t_command *c, int *p, t_minishell *m, t_rdir *i)
{
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
	set_bkp_fd(i);
	apply_redirects(i);
	return (0);
}

static void	expand_and_clean_args(t_command *cmd, t_minishell *mini)
{
	int		i;
	char	*tmp;

	i = 0;
	while (cmd->argv[i])
	{
		tmp = expand_variables(cmd->argv[i], mini->status, mini->envlist);
		free(cmd->argv[i]);
		cmd->argv[i++] = remove_quotes(tmp);
	}
}

static	int	exec_handler(t_command *cmd, t_minishell *mini, int *p, t_rdir *info)
{
	if (handle_redirect_and_pipe(cmd, p, mini, info))
		return (1);
	cmd->argv = prepare_exec_argv(cmd->argv, &cmd->argc);
	expand_and_clean_args(cmd, mini);
	if (cmd->next)
	{
		exec_pattern(cmd, p, mini);
		mini->in_fd = p[READ];
	}
	else
		exec_pattern(cmd, NULL, mini);
	restore_io(info);
	return (0);
}

void	ft_exec_v6(t_minishell *mini)
{
	t_command	*cmd;
	int			p[2];
	t_rdir		*info;

	cmd = mini->cmd;
	while (cmd)
	{
		info = init_redirect(); // リダイレクトの初期化
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
}
