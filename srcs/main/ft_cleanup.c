/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cleanup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 18:50:56 by shonakam          #+#    #+#             */
/*   Updated: 2025/02/18 14:49:06 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	get_exit_status(t_minishell *mini)
{
	printf("exited with status \033[0;32m%d\033[0m\n", mini->status);
	return (mini->status);
}

void	ft_clean_child(t_minishell *mini)
{
	int	status;

	status = mini->status;
	free(mini->line);
	free_tokens(mini->token);
	free_commands(mini->cmd);
	free_envlist(&mini->envlist);
	free(mini);
	clear_history();
	exit(status);
}

void	ft_clean(t_minishell *mini, int level)
{
	if (mini->line && level >= 0)
		free(mini->line);
	if (mini->token && level >= 1)
		free_tokens(mini->token);
	if (mini->cmd && level >= 2)
		free_commands(mini->cmd);
	if (mini->envlist && level >= 3)
		free_envlist(&mini->envlist);
	mini->in_fd = STDIN_FILENO;
	mini->hd_index = 0;
}

void	ft_clean_exit(t_minishell *mini)
{
	int	status;

	ft_putendl_fd("exit", STDOUT_FILENO);
	free_envlist(&mini->envlist);
	status = mini->status;
	free(mini);
	clear_history();
	exit(status);
}
