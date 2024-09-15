/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_v5.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 06:20:22 by shonakam          #+#    #+#             */
/*   Updated: 2024/09/16 03:31:09 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

// void	handle_errors(void)
// {
// 	FILE	*err_file;
// 	char	buf[1024];

// 	err_file = fopen("/tmp/minishell_err", "r");
// 	if (err_file)
// 	{
// 		while (fgets(buf, sizeof(buf), err_file))
// 		{
// 			fprintf(stderr, "%s", buf);
// 		}
// 		fclose(err_file);
// 		unlink("/tmp/minishell_err"); // 使用後に削除
// 	}
// }

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

void	print_commands(t_command *cmd)
{
	if (!cmd)
		return ;
	printf("----- PRINT CMD -----\n");
	for (int i=0; cmd; i++) {
		printf("cmd[%d] argc: %d\n", i, cmd->argc);
		for (int j = 0; cmd->argv && cmd->argv[j]; j++)
			printf("cmd[%d] argv[%d]: %s\n", i, j, cmd->argv[j]);
		// printf("cmd[%d] append_fd: %d\n", i, cmd->append_fd);
		// printf("cmd[%d] imput_fd: %d\n", i, cmd->input_fd);
		// printf("cmd[%d] output_fd: %d\n", i, cmd->output_fd);
		printf("\n");
		cmd = cmd->next;
	}
	printf("---------------------\n");
}

/*
-- heredocは最後のみ解釈？
-- cat <<e <<f なら <<f を表示
*/
void	ft_exec_v5(t_minishell *mini)
{
	t_command	*cmd;
	int			p[2];

	cmd = mini->cmd;
	while (cmd)
	{
		if (cmd->next)
		{
			if (pipe(p) == -1)
			{
				perror("pipe");
				exit(EXIT_FAILURE);
			}
		}
		if (handle_heredoc(cmd, &mini->hd_index) == 1)
		{
			printf("\033[31mBREAKPOINT\033[0m\n");
			cmd = cmd->next;
			continue ;
		}
		if (cmd->hd_list)
			rebuild_args(cmd);
		// print_commands(cmd);
		exec_pattern(cmd, p, mini);
		cmd = cmd->next;
	}
	while (waitpid(-1, &mini->status, 0) > 0)
		;
	
}