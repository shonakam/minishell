/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 18:50:56 by shonakam          #+#    #+#             */
/*   Updated: 2024/09/06 19:32:42 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	ft_clean(t_minishell *mini, int flag)
{
	if (mini->line)
		free(mini->line);
	if (mini->token)
		free_tokens(mini->token);
	if (mini->cmd)
		free_close_commands(mini->cmd);
	if (mini->envlist && flag == 1)
		free_envlist(&mini->envlist);
}

void	ft_clean_exit(t_minishell *mini)
{
	ft_clean(mini, 1);
	exit(EXIT_SUCCESS);
}
