/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_v7.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 08:21:18 by shonakam          #+#    #+#             */
/*   Updated: 2025/02/12 21:56:15 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static void	exec_handler(
	t_command *cmd, t_minishell *mini, int *pipe, t_rdir *info)
{
	handle_pipe(cmd, pipe, 0);
	if (process_heredoc(cmd, pipe, mini))
		return ;
	cmd->argv = prepare_exec_argv(cmd->argv, &cmd->argc, 0, 0);
	if (!cmd->argv)
		return ;
	expand_and_clean_args(cmd, mini);
	if (cmd->next)
	{
		set_backup_fd(info);
		exec_pattern(cmd, pipe, mini, info);
		mini->in_fd = pipe[READ];
	}
	else
		exec_pattern(cmd, NULL, mini, info);
	restore_backup_io(info);
}

void	ft_exec_v7(t_minishell *mini)
{
	t_command	*cmd;
	t_rdir		*info;
	int			pipe[2];

	cmd = mini->cmd;
	while (cmd)
	{
		info = init_redirect();
		mini->status = parse_redirects(cmd, info);
		if (info->rdir_i != INT_MIN)
			exec_handler(cmd, mini, pipe, info);
		free(info);
		cmd = cmd->next;
	}
	while (waitpid(-1, &mini->status, 0) > 0)
		;
	mini->status = parse_exit_status(mini->status);
}
