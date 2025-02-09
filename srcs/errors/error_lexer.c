/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_lexer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 08:35:56 by shonakam          #+#    #+#             */
/*   Updated: 2025/02/04 10:39:42 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static	int	print_syntax_error(int n)
{
	char	*s;

	if (n == 0)
	{
		s = "minishell: syntax error near unexpected token `|'\n";
		write(2, s, ft_strlen(s));
	}
	if (n == 1)
	{
		s = "minishell: syntax error near unexpected token `newline'\n";
		write(2, s, ft_strlen(s));
	}
	return (1);
}

t_token	**check_unexpected_token(t_token **t)
{
	int	flag;

	flag = 0;
	if (!t[0] || !t)
		return (free_tokens(t), NULL);
	if (t[0]->type == METACHAR_PIPE)
		flag += print_syntax_error(0);
	if (t[0]->type == METACHAR_INPUT_REDIRECT
		|| t[0]->type == METACHAR_OUTPUT_REDIRECT
		|| t[0]->type == METACHAR_APPEND_REDIRECT)
		flag += print_syntax_error(1);
	if (flag)
		return (free_tokens(t), NULL);
	return (t);
}

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