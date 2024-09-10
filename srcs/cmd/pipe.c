/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 22:55:59 by shonakam          #+#    #+#             */
/*   Updated: 2024/09/08 23:47:30 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

// void execute_command(t_command *cmd, t_minishell *mini)
// {
// 	char	*path;

// 	dup_descriptor(cmd);
// 	path = get_bin_path(mini->envlist, cmd->argv[0]);
// 	execve(path, cmd->argv, convert_to_envp(&mini->envlist));
// 	perror("execute_command: execve");
// }

// int	**create_pipe(int n_cmds)
// {
// 	int	**pipes;
// 	int	i;

// 	pipes = (int **)malloc(sizeof(int *) * (n_cmds - 1));
// 	if (!pipes)
// 		perror("create_pipe: malloc");
// 	i = 0;
// 	while (i < n_cmds - 1)
// 	{
// 		pipes[i] = (int *)malloc(sizeof(int) * 2);
// 		if (!pipes[i])
// 			perror("create_pipe: malloc");
// 		if (pipe(pipes[i]) == -1)
// 			perror("create_pipe: pipe");
// 		i++;
// 	}
// 	return (pipes);
// }

// void	close_pipe(int **pipes, int n_cmds)
// {
// 	int	i;

// 	i = 0;
// 	while (i < n_cmds - 1)
// 	{
// 		close(pipes[i][READ]);
// 		close(pipes[i][WRITE]);
// 		free(pipes[i]);
// 		i++;
// 	}
// 	free(pipes);
// }

// void fork_and_execute(int i, int n_cmds, int **pipes, t_command *cmd)
// {
// 	pid_t pid;

// 	pid = fork();
// 	if (pid == -1)
// 		perror("fork");
// 	if (pid == 0)
// 	{
// 		if (i > 0)
// 			dup2(pipes[i - 1][READ], STDIN_FILENO);
// 		if (i < n_cmds - 1)
// 			dup2(pipes[i][WRITE], STDOUT_FILENO);
// 		close_all_pipes(n_cmds - 1, pipes);
// 		execute_command(cmd);
// 	}
// }
