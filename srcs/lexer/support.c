/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   support.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 21:39:46 by shonakam          #+#    #+#             */
/*   Updated: 2024/09/01 21:39:48 by shonakam         ###   ########.fr       */
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

// test
void	print_tokens(t_token **tokens)
{
	if (!tokens)
		return ;
	for (int i=0; tokens[i]; i++) {
		printf("token[%d]: %s\n", i, tokens[i]->word);
	}
}
