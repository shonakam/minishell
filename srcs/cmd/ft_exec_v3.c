/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_v3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 00:01:53 by shonakam          #+#    #+#             */
/*   Updated: 2024/09/12 14:47:40 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static void exec_cmd(t_command *cmd, t_pipe *i, t_pipe *o, t_minishell *mini)
{
	pid_t	pid;
	char	*path;

	pid = fork();
	if (pid == -1)
		perror("fork");
	if (pid == 0)
	{
		dup_handler(i, o);
		path = get_bin_path(mini->envlist, cmd->argv[0]);
		execve(path, cmd->argv, convert_to_envp(&mini->envlist));
		perror("command not found: ");
		exit(EXIT_FAILURE);
	}
}

static void create_pipe(t_pipe *p)
{
	int	err;
	int	fd[2];

	err = pipe(fd);
	if (err == -1)
	{
		perror("pipe");
	}
	p->read_end = fd[READ];
	p->write_end = fd[WRITE];
}

static t_pipe *get_input_pipe(t_command *cmd, t_pipe *in, t_minishell *mini)
{
	if (cmd == mini->cmd)
		return (NULL);
	return (in);
}

static t_pipe *get_output_pipe(t_command *cmd, t_pipe *out)
{
	if (cmd->next == NULL)
		return (NULL);
	return (out);
}

void	ft_exec_v3(t_minishell *mini)
{
	t_pipe		pipe_in;
	t_pipe		pipe_out;
	t_command	*cmd;

	initialize_pipes(&pipe_in, &pipe_out);
	cmd = mini->cmd;
	while (cmd)
	{
		if (cmd->next)
			create_pipe(&pipe_out);
		exec_cmd(cmd,
			get_input_pipe(cmd, &pipe_in, mini),		// Use pipe_in if not the first command
			get_output_pipe(cmd, &pipe_out), mini);		// Use pipe_out if there’s a next command
		if (pipe_in.read_end != -1)
			close_pipe(&pipe_in);
		pipe_in = pipe_out;
		cmd = cmd->next;
	}
	if (pipe_in.read_end != -1)
		close_pipe(&pipe_in);
	while (waitpid(-1, &mini->status, 0) > 0)
		;
}