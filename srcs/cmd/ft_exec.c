/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 16:44:14 by shonakam          #+#    #+#             */
/*   Updated: 2024/09/07 02:11:29 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

// create_pipe
// need [pipe * 2] child_processes
static int	*create_pipes(int n)
{
	int	*pipe_fds;
	int	err;
	int	i;
	
	pipe_fds = (int *)malloc(sizeof(int) * (n * 2));
	if (pipe_fds == NULL) {
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (i < n)
	{
		err = pipe(pipe_fds + (i * 2));
		if (err == -1)
		{
			perror("create_pipes: pipe");
			free(pipe_fds);
			exit(EXIT_FAILURE);
		}
		i++;
	}
	return (pipe_fds);
}

// int	execute_command(char *cmd, int *p_fds, int p_index, int num_pipes)
// {
// 	pid_t pid = fork();
// 	if (pid == -1)
// 	{
// 		perror("fork");
// 		exit(EXIT_FAILURE);
// 	}

// 	if (pid == 0)
// 	{
		
// 	}
// }

// シンプルなテスト
int	ft_exec(t_minishell *mini)
{
	int	*pipe_fds;
	int	status;

	pipe_fds = create_pipes(count_pipechar(mini->token));
	(void)pipe_fds;
	// pid_t	pid;

	pid_t pid = fork();
	if (pid == 0)
	{
		char *cmd = mini->cmd->argv[0];
		char *bin_path = get_bin_path(mini->envlist, cmd);
		char **envp = convert_to_envp(&mini->envlist);

		// プロセスの置き換え
		if (execve(bin_path, mini->cmd->argv, envp) == -1)
		{
			print_error("command not found", mini->cmd->argv[0]);
			exit(EXIT_FAILURE);  // エラーが発生した場合は子プロセスを終了する
		}
	}
	else
	{
		// 子プロセスの終了を待機
		if (waitpid(pid, &status, 0) == -1)
		{
			perror("waitpid");
			return EXIT_FAILURE;
		}
	}
	
	return (0);
}
