/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 16:44:14 by shonakam          #+#    #+#             */
/*   Updated: 2024/09/04 16:13:44 by shonakam         ###   ########.fr       */
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
			perror("pipe");
			free(pipe_fds);
			exit(EXIT_FAILURE);
		}
		i++;
	}
	return (pipe_fds);
}

void execute_command(char *cmd, int *p_fds, int p_index, int num_pipes)
{
	pid_t pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}

	if (pid == 0)
	{
		
	}
}

// シンプルなテスト
int	ft_exec(t_token **tokens)
{
	int	*pipe_fds;

	pipe_fds = create_pipes(count_pipechar(tokens));

	// pid_t	pid;
	
	return (0);
}