/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_v5.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 06:20:22 by shonakam          #+#    #+#             */
/*   Updated: 2024/09/18 03:59:52 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static void	exec_bin(t_command *cmd, int *p, t_minishell *mini)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		if (mini->in_fd != STDIN_FILENO)
			redirect_fd(mini->in_fd, STDIN_FILENO);
		if (p && cmd->next)
		{
			close(p[READ]);
			redirect_fd(p[WRITE], STDOUT_FILENO);
		}
		execve(get_bin_path(mini->envlist, cmd->argv[0]),
			cmd->argv, convert_to_envp(&mini->envlist));
		perror("execve");
		exit(EXIT_FAILURE);
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
			builtin_runner(cmd, 0, mini->envlist);
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

static	int	exec_handler(t_command	*cmd, t_minishell *m, int *p)
{
	int		i;
	char 	*tmp;

	if (cmd->next)
			handle_pipe(p, 0);
	if (handle_heredoc(cmd, &m->hd_index, m->status, m->envlist) == 1)
	{
		m->status = 0;
		if (cmd->next)
			handle_pipe(p, 1);
		return (1);
	}
	if (cmd->hd_list)
		rebuild_args(cmd);
	i = 0;
	while (cmd->argv[i])
	{
		tmp = expand_variables(cmd->argv[i], m->status, m->envlist);
		free(cmd->argv[i]);
		cmd->argv[i++] = remove_quotes(tmp);
	}
	return (exec_pattern(cmd, p, m), 0);
}


/*
-- manage heredoc
-- expand args
-- redirect | bin / builtins
-- export TMP=s1 > cat "$TMP" ok
*/
void	ft_exec_v5(t_minishell *mini)
{
	t_command	*cmd;
	int			p[2];

	cmd = mini->cmd;
	while (cmd)
	{
		printf("\033[31mBREAKPOINT\033[0m\n");
		if (exec_handler(cmd, mini, p))
		{
			cmd = cmd->next;
			continue ;
		}
		cmd = cmd->next;
	}
	while (waitpid(-1, &mini->status, 0) > 0)
		;
}
