/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_unsupported_syntax.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 11:30:12 by shonakam          #+#    #+#             */
/*   Updated: 2025/02/15 19:21:55 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static int	unsupported_matcher(t_token **t, int i)
{
	if (t[i]->type == METACHAR_PIPE
		&& t[i + 1] && t[i + 1]->type == METACHAR_PIPE)
	{
		ft_putendl_fd("minishell: unsupported syntax `||\"", STDERR_FILENO);
		return (1);
	}
	if (t[i]->type == METACHAR_AND
		&& t[i + 1] && t[i + 1]->type == METACHAR_AND)
	{
		ft_putendl_fd("minishell: unsupported syntax `&&\"", STDERR_FILENO);
		return (1);
	}
	return (0);
}

int	valid_unsupported_tokens(t_token **tokens)
{
	int		have_quote;
	size_t	i;

	have_quote = 0;
	i = 0;
	while (tokens[i])
	{
		have_quote = find_quotes(tokens[i]->word);
		if (!have_quote && unsupported_matcher(tokens, i))
			return (SYNTAX_ERRNO);
		i++;
	}
	return (0);
}
