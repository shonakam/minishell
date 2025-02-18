/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 10:27:26 by shonakam          #+#    #+#             */
/*   Updated: 2025/02/18 14:46:23 by shonakam         ###   ########.fr       */
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

void	exec_pattern(t_command *c, int *p, t_minishell *m, t_rdir *i)
{
	set_backup_fd(i);
	if (is_builtin(c))
	{
		return (handle_builtin(c, p, m, i));
	}
	if (apply_redirects(i))
	{
		return (ft_clean(m, 3));
	}
	if (c->next)
	{
		exec_bin(i, c, p, m);
		m->in_fd = p[READ];
	}
	else
		exec_bin(i, c, NULL, m);
}

void	expand_and_clean_args(t_command *cmd, t_minishell *mini)
{
	int		i;
	char	*tmp;

	i = 0;
	while (cmd->argv && cmd->argv[i])
	{
		tmp = expand_variables(
				cmd->argv[i], mini->backup_status, mini->envlist);
		free(cmd->argv[i]);
		cmd->argv[i++] = remove_quotes(tmp);
		free(tmp);
	}
}

int	process_heredoc(t_command *cmd, int *pipe, t_minishell *mini)
{
	handle_heredoc(
		cmd, &mini->hd_index, mini->backup_status, mini->envlist);
	if (g_signal_flag & (1 << 1))
		return (1);
	if (cmd->hd_list && ft_strcmp(cmd->argv[0], "<<") == 0)
	{
		mini->status = 0;
		handle_pipe(cmd, pipe, 1);
		return (1);
	}
	if (cmd->hd_list)
		rebuild_args(cmd);
	return (0);
}
