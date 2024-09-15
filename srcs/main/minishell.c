/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 15:57:54 by mosh              #+#    #+#             */
/*   Updated: 2024/09/15 22:00:24 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

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

static t_minishell	*init_mini(t_minishell *mini, char **envp)
{
	mini->line = NULL;
	mini->token = NULL;
	mini->cmd = NULL;
	mini->in_fd = STDIN_FILENO;
	mini->hd_index = 0;
	mini->status = 0;
	mini->envlist = make_envlist(envp);
	if (!mini->envlist)
		return (NULL);
	return (mini);
}

static void	minishell(t_minishell *mini)
{
	if (!mini)
	{
		perror("minishell: insufficient memory or system resources\n");
		exit(EXIT_FAILURE);
	}
	while (INT_MAX)
	{
		mini->line = readline("minishell$ ");
		if (mini->line == NULL)
			continue ;
		mini->token = ft_lexer(mini->line); // '|'や'>>'で終わる不完全な文字列は連続して入力を受け続ける
		if (mini->token == NULL)
			continue ;
		mini->cmd = build_commands(mini->token, count_tokens(mini->token));
		// print_commands(mini->cmd);
		ft_exec_v5(mini);
		ft_clean(mini, 0);
		get_exit_status(mini);
		// return ;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_minishell	mini;

	(void)argc;
	(void)argv;
	minishell(init_mini(&mini, envp));
	return (0);
}

__attribute__((destructor))
static void destructor() {
	system("leaks -q minishell");
}
