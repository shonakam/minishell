/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 13:20:01 by shonakam          #+#    #+#             */
/*   Updated: 2025/02/14 18:47:18 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	valid_quote(const char *s)
{
	char	active_quote;

	active_quote = '\0';
	while (*s)
	{
		if ((*s == '\'' || *s == '"'))
		{
			if (active_quote == '\0')
				active_quote = *s;
			else if (*s == active_quote)
				active_quote = '\0';
		}
		s++;
	}
	return (active_quote == '\0');
}

int	find_quotes(const char *token)
{
	while (*token)
	{
		if (*token == '\'' || *token == '\"')
			return (1);
		token++;
	}
	return (0);
}

int	count_tokens(t_token **tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
		i++;
	return (i);
}

void	free_tokens(t_token **tokens)
{
	int	i;

	if (tokens == NULL)
		return ;
	i = 0;
	while (tokens[i])
	{
		free(tokens[i]->word);
		free(tokens[i]);
		tokens[i++] = NULL;
	}
	free(tokens);
}
