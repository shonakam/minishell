/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_v1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 16:44:14 by shonakam          #+#    #+#             */
/*   Updated: 2024/09/11 15:28:24 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

// static void execute_command(t_command *cmd, t_minishell *mini)
// {
// 	char	*path;

// 	dup_descriptor(cmd);
// 	path = get_bin_path(mini->envlist, cmd->argv[0]);
// 	execve(path, cmd->argv, convert_to_envp(&mini->envlist));
// 	perror("execute_command: execve");
// }

// static int	handle_fork(t_command *cmd, t_minishell *mini)
// {
// 	pid_t	pid;

// 	pid = fork();
// 	if (pid == -1)
// 		return (perror("handle_fork: fork1"), -1);
// 	if (pid == 0)
// 		execute_command(cmd, mini);
// 	return pid;
// }

// static void	handle_pipe_io(t_command *l, t_command *r)
// {
// 	int	fds[2];
// 	int	err;

// 	err = pipe(fds);
// 	if (err == -1)
// 	{
// 		perror("handle_pipe_io: pipe");
// 		return ;
// 	}
// 	l->output_fd = fds[WRITE];
// 	r->input_fd = fds[READ];
// }

// static void	handle_close(t_command *head, t_command *cmd)
// {
// 	if (head != cmd && cmd->input_fd != STDIN_FILENO)
// 	{
// 		printf("CLOSE_IN\n");
// 		close(cmd->input_fd);
// 	}
// 	if (cmd->output_fd != STDOUT_FILENO)
// 	{
// 		printf("CLOSE_OUT\n");
// 		close(cmd->output_fd);
// 	}
// }

// void	ft_exec_v1(t_minishell *mini)
// {
// 	t_command	*left;
// 	t_command	*right;

// 	left = mini->cmd;
// 	while (left)
// 	{
// 		right = left->next;
// 		if (right)
// 			handle_pipe_io(left, right);
// 		if (handle_fork(left, mini) == -1)
// 			return ;
// 		handle_close(mini->cmd, left);
// 		left = right;
// 	}
// 	close(STDIN_FILENO);
// 	close(STDOUT_FILENO);
// 	while (waitpid(-1, &mini->status, 0) > 0);
// 	open("/dev/tty", O_RDONLY);
// 	open("/dev/tty", O_WRONLY);
// 	printf(">> END EXEC\n");
// }
