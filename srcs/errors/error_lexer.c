/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_lexer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 08:35:56 by shonakam          #+#    #+#             */
/*   Updated: 2024/09/19 08:36:07 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	syntax_err(int n)
{
	if (n == -5)
	{
		ft_putendl_fd(
			"minishell: syntax error near unexpected token `||'",
			STDERR_FILENO);
	}
	else if (n == -9)
	{
		ft_putendl_fd(
			"minishell: syntax error near unexpected token `|'",
			STDERR_FILENO);
	}
	else
	{
		ft_putendl_fd(
			"minishell: syntax error near unexpected token `newline'",
			STDERR_FILENO);
	}
	
}