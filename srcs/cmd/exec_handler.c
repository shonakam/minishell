/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 10:27:26 by shonakam          #+#    #+#             */
/*   Updated: 2025/02/09 07:38:45 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static void	handle_builtin(t_command *c, int *p, t_minishell *m, t_rdir *i)
{
	int	fd;

	if (c->next)
	{
		if (i->rdir_o != -1)
		{
			builtin_runner(c, i->rdir_o, m->envlist);
			m->in_fd = i->i_bkp;
		}
		else
		{
			builtin_runner(c, p[WRITE], m->envlist);
			m->in_fd = p[READ];
		}
		close(p[WRITE]);
	}
	else
	{
		fd = 0;
		if (i->rdir_i != -1)
			fd = i->rdir_i;
		else if (i->rdir_o != -1)
			fd = i->rdir_o;
		m->status = builtin_runner(c, fd, m->envlist);
	}
}

static void	exec_pattern(t_command *c, int *p, t_minishell *m, t_rdir *i)
{
	set_bkp_fd(i);
	if (is_builtin(c))
		return (handle_builtin(c, p, m, i));
	apply_redirects(i);
	if (c->next)
	{
		exec_bin(c, p, m);
		m->in_fd = p[READ];
	}
	else
		exec_bin(c, NULL, m);
}

static int	handle_redirect_and_pipe(t_command *c, int *p, t_minishell *m)
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
		free(tmp);
	}
}

int	exec_handler(t_command *c, t_minishell *m, int *p, t_rdir *i)
{
	if (handle_redirect_and_pipe(c, p, m))
		return (1);
	c->argv = prepare_exec_argv(c->argv, &c->argc);
	expand_and_clean_args(c, m);
	if (c->next)
	{
		set_bkp_fd(i);
		exec_pattern(c, p, m, i);
		m->in_fd = p[READ];
	}
	else
		exec_pattern(c, NULL, m, i);
	restore_io(i);
	return (0);
}
