/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_v4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 00:01:53 by shonakam          #+#    #+#             */
/*   Updated: 2024/09/14 17:22:12 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "includes/minishell.h"

// static void exec_cmd(t_command *cmd, t_pipe *i, t_pipe *o, t_minishell *mini)
// {
// 	pid_t	pid;
// 	char	*path;
// 	char	*s;

// 	pid = fork();
// 	if (pid == -1)
// 		exit(EXIT_FAILURE);
// 	if (pid == 0)
// 	{
// 		if (!is_builtin(cmd))
// 		{
// 			if (i && i->read_end != -1) {
// 				printf("i->read_end [%d]\n", i->write_end);
// 				close(i->write_end);
// 				dup2(i->read_end, STDIN_FILENO); // 前のコマンドからの入力リダイレクト
// 				close(i->read_end);
// 			}
// 			if (o && o->write_end != -1) {
// 				close(o->read_end);
// 				dup2(o->write_end, STDOUT_FILENO); // 次のコマンドへの出力リダイレクト
// 				close(o->write_end);
// 			}
// 			printf("\x1b[31m [BREAK-POINT] \x1b[0m\n");
// 			path = get_bin_path(mini->envlist, cmd->argv[0]);
// 			execve(path, cmd->argv, convert_to_envp(&mini->envlist));
// 			s = concat_vars(3, "minishell: ",
// 				cmd->argv[0], ": command not found\n");
// 			write(2, s, ft_strlen(s));
// 			free(s);
// 			exit(127);
// 		}
// 		exit(0);
// 	}
// 	else // exec builtins
// 	{
// 		if (is_builtin(cmd))
// 		{
// 			// if (i && i->read_end != -1)
// 			// {
// 			// 	close(i->write_end);
// 			// 	// mini->status = execute_builtin(cmd, i->read_end);
// 			// 	close(i->read_end);
// 			// }
// 			if (o && o->write_end != -1)
// 			{
// 				printf("o->write_end [%d]\n", o->write_end);
// 				if (1)
// 				{
// 					// while (waitpid(pid, &mini->status, 0) > 0)
// 					close(o->read_end);
// 					mini->status = execute_builtin(cmd, o->write_end);
// 					close(o->write_end);
// 					wait(NULL);
// 				}
// 			}
// 			else
// 				mini->status = execute_builtin(cmd, STDOUT_FILENO);
// 		}
// 	}
// }

// static void create_pipe(t_pipe *p)
// {
// 	int	err;
// 	int	fd[2];

// 	err = pipe(fd);
// 	if (err == -1)
// 	{
// 		perror("pipe");
// 	}
// 	p->read_end = fd[READ];
// 	p->write_end = fd[WRITE];
// }

// static t_pipe *get_input_pipe(t_command *cmd, t_pipe *in, t_minishell *mini)
// {
// 	if (cmd == mini->cmd)
// 		return (NULL);
// 	return (in);
// }

// static t_pipe *get_output_pipe(t_command *cmd, t_pipe *out)
// {
// 	if (cmd->next == NULL)
// 		return (NULL);
// 	return (out);
// }

// void	ft_exec_v4(t_minishell *mini)
// {
// 	t_pipe		pipe_in;
// 	t_pipe		pipe_out;
// 	t_command	*cmd;

// 	initialize_pipes(&pipe_in, &pipe_out);
// 	cmd = mini->cmd;
// 	while (cmd)
// 	{
// 		if (cmd->next)
// 			create_pipe(&pipe_out);
// 		exec_cmd(cmd,
// 			get_input_pipe(cmd, &pipe_in, mini),		// Use pipe_in if not the first command
// 			get_output_pipe(cmd, &pipe_out), mini);		// Use pipe_out if there’s a next command
// 		if (pipe_in.read_end != -1)
// 			close_pipe(&pipe_in);
// 		pipe_in = pipe_out;
// 		cmd = cmd->next;
// 	}
// 	if (pipe_in.read_end != -1)
// 		close_pipe(&pipe_in);
// 	if (pipe_out.read_end != -1)
// 		close_pipe(&pipe_out);
// 	while (waitpid(-1, &mini->status, 0) > 0)
// 		;
// }
