/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_v7.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 08:21:18 by shonakam          #+#    #+#             */
/*   Updated: 2025/02/19 15:20:03 by shonakam         ###   ########.fr       */
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

static void	exec_handler(
	t_command *cmd, t_minishell *mini, int *pipe, t_rdir *info)
{
	handle_pipe(cmd, pipe, 0);
	if (process_heredoc(cmd, pipe, mini))
		return ;
	cmd->argv = prepare_exec_argv(cmd->argv, &cmd->argc, 0, 0);
	if (!cmd->argv || !cmd->argv[0])
	{
		return ;
	}
	expand_and_clean_args(cmd, mini);
	if (cmd->next)
	{
		exec_pattern(cmd, pipe, mini, info);
		mini->in_fd = pipe[READ];
	}
	else
	{	
		exec_pattern(cmd, NULL, mini, info);
	}
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
		if (valid_redirect_sequence(cmd->argv))
		{
			cmd = cmd->next;
			free_info(info);
			continue ;
		}
		if (info->rdir_i != INT_MIN && mini->status != 1)
		{
			exec_handler(cmd, mini, pipe, info);
		}
		free_info(info);
		cmd = cmd->next;
	}
	while (waitpid(-1, &mini->status, 0) > 0)
		;
	mini->status = parse_exit_status(mini->status);
}
