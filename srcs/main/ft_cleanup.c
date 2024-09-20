/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cleanup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 18:50:56 by shonakam          #+#    #+#             */
/*   Updated: 2024/09/20 23:57:16 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	get_exit_status(t_minishell *mini)
{
	// printf("exited with status \033[0;32m%d\033[0m\n", WEXITSTATUS(mini->status));
	printf("exited with status \033[0;32m%d\033[0m\n", mini->status);
	return (mini->status);
}

void	ft_clean(t_minishell *mini, int flag)
{
	if (mini->line)
		free(mini->line);
	if (mini->token)
		free_tokens(mini->token);
	if (mini->cmd)
		free_commands(mini->cmd);
	if (mini->envlist && flag == 1)
		free_envlist(&mini->envlist);
	mini->in_fd = STDIN_FILENO;
	mini->hd_index = 0;
}

void	ft_clean_exit(t_minishell *mini)
{
	// ft_clean(mini, 1);
	ft_putendl_fd("exit", STDOUT_FILENO);
	// free(mini);
	exit(mini->status);
	// exit(EXIT_SUCCESS);
}
