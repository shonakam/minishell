/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_v2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 16:44:14 by shonakam          #+#    #+#             */
/*   Updated: 2024/09/14 20:17:51 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "includes/minishell.h"

// static void execute_command(t_command *cmd, t_minishell *mini)
// {
// 	char	*path;

// 	dup_descriptor(cmd);
// 	path = get_bin_path(mini->envlist, cmd->argv[0]);
// 	execve(path, cmd->argv, convert_to_envp(&mini->envlist));
// 	perror("execute_command: execve");
// }

// static int	**create_pipe(int n_cmds)
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

// static void	close_pipe(int **pipes, int n_cmds)
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

// static void fork_and_execute(t_pipe *p, t_command *cmd, t_minishell *mini)
// {
// 	pid_t pid;

// 	pid = fork();
// 	if (pid == -1)
// 		perror("fork");
// 	if (pid == 0)
// 	{
// 		// if (p->index > 0)
// 		// 	dup2(p->pipes[p->index - 1][READ], STDIN_FILENO);
// 		// if (p->index < p->n_cmds - 1)
// 		// 	dup2(p->pipes[p->index][WRITE], STDOUT_FILENO);
// 		// close_pipe(p->pipes, p->n_cmds - 1);
// 		execute_command(cmd, mini);
// 		exit(EXIT_SUCCESS); 
// 	}
// }

// 処理の優先順位は？- builtin, heredoc, リダイレクト, bin, 実行ファイル？
// heredocはexecute_commandで処理する？
// パイプの閉じる時を調整する必要あり
// 最後のコマンドoutputをSTDOUT_FILENOにしないと戻ってこない
// statusを$?に格納
// void	ft_exec_v2(t_minishell *mini)
// {
// 	int			status;
// 	t_pipe		pipe;

// 	pipe.n_cmds = count_cmd(mini->cmd);
// 	pipe.pipes = create_pipe(pipe.n_cmds);
// 	pipe.index = 0;
// 	while (pipe.index < pipe.n_cmds)
// 	{
// 		fork_and_execute(&pipe, mini->cmd, mini);
// 		mini->cmd = mini->cmd->next;
// 		pipe.index++;
// 	}
// 	close_pipe(pipe.pipes, pipe.n_cmds - 1);
// 	pipe.index = 0;
// 	while (pipe.index < pipe.n_cmds)
// 	{
// 		waitpid(-1, &status, 0); 
// 		pipe.index++;
// 	}
// 	// while (waitpid(-1, &status, 0) > 0);
// }
