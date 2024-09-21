/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 10:27:26 by shonakam          #+#    #+#             */
/*   Updated: 2024/09/21 01:52:31 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

/* 
--  [pwd > s2 | cat -e] bash-5.2ではcatに入力はな👍
-- 
	1. builtins or bin
*/
static void	exec_pattern(t_command *c, int *p, t_minishell *m, t_rdir *i)
{
	set_bkp_fd(i);
	if (is_builtin(c))
	{
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
			if (i->rdir_i != -1)
				m->status = builtin_runner(c, i->rdir_i, m->envlist);
			else if (i->rdir_o != -1) 
				m->status = builtin_runner(c, i->rdir_o, m->envlist);
			else
				m->status = builtin_runner(c, 0, m->envlist);
		}
	}
	else
	{
		apply_redirects(i);
		if (c->next)
		{
			exec_bin(c, p, m);
			m->in_fd = p[READ];
		}
		else
			exec_bin(c, NULL, m);
	}
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

/*
	Handles the execution of commands by:
	1. リダイレクトとパイプの処理
	2. 実行用の引数配列を再構築
	3. 引数の展開とクリーンアップ
	4. EXECUTTION😎
		- nextがある(pipe)か確認 -> pipeを接続 / NULL
	5. fdを復元
*/
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

