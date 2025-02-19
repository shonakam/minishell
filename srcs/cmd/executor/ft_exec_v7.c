/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_v7.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 08:21:18 by shonakam          #+#    #+#             */
/*   Updated: 2025/02/20 00:37:18 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	free_info(t_rdir *info)
{
	if (info->rdir_i != -1 && info->rdir_i != INT_MIN)
		close(info->rdir_i);
	if (info->rdir_o != -1 && info->rdir_o != INT_MIN)
		close(info->rdir_o);
	free(info);
}

static void	set_is_builtin(t_command *cmd, int *f)
{
	if (is_builtin(cmd))
		*f = 1;
	else
		*f = 0;
}

static void setup_pipe_or_redirect(t_command *c, int *p, t_rdir *i)
{
	if (!c->next)
		return ;
	if (pipe(p) == -1)
	{
		print_syscall_error("pipe: setup_pipe_or_redirect", 0);
		exit(EXIT_FAILURE);
	}
	if (check_fd(i->rdir_i))
		close(p[READ]);
	if (check_fd(i->rdir_o))
		close(p[WRITE]);
}

static void	exec_handler(
	t_command *cmd, t_minishell *mini, int *pipe, t_rdir *info)
{
	setup_pipe_or_redirect(cmd, pipe, info);
	if (process_heredoc(cmd, mini))
		return ;
	cmd->argv = prepare_exec_argv(cmd->argv, &cmd->argc, 0, 0);
	if (!cmd->argv || !cmd->argv[0])
		return ;
	expand_and_clean_args(cmd, mini);
	if (cmd->next)
	{
		exec_pattern(cmd, pipe, mini, info);
		mini->in_fd = pipe[READ];
	}
	else
		exec_pattern(cmd, NULL, mini, info);
}

void	ft_exec_v7(t_minishell *mini)
{
	t_command	*cmd;
	t_rdir		*info;
	int			pipe[2];
	int			last_is_builtin;

	cmd = mini->cmd;
	while (cmd)
	{
		info = init_redirect();
		mini->status = parse_redirects(cmd, info);
		if (mini->status != 1)
		{
			exec_handler(cmd, mini, pipe, info);
		}
		free_info(info);
		set_is_builtin(cmd, &last_is_builtin);
		cmd = cmd->next;
	}
	while (waitpid(-1, &mini->status, 0) > 0)
		;
	if (!last_is_builtin)
		mini->status = parse_exit_status(mini->status);
}
