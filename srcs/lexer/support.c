/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   support.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 21:39:46 by shonakam          #+#    #+#             */
/*   Updated: 2024/09/06 17:23:27 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	valid_quote(const char *s)
{
	size_t	single_q;
	size_t	double_q;

	single_q = 0;
	double_q = 0;
	while (*s != '\0')
	{
		if (*s == '\'')
			single_q++;
		else if (*s == '"')
			double_q++;
		s++;
	}
	if ((single_q % 2 != 0) || (double_q % 2 != 0))
		return (0);
	return (1);
}

int	ft_isspace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n')
		return (1);
	return (0);
}

void	free_tokens(t_token **tokens)
{
	int	i;

	if (tokens == NULL)
		return;
	i = 0;
	while(tokens[i])
	{
		free(tokens[i]->word);
		free(tokens[i++]);
	}
	free(tokens);
}

int	count_tokens(t_token **tokens)
{
	int	i;

	i = 0;
	while(tokens[i])
		i++;
	return (i);
}
