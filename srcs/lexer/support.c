/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   support.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 21:39:46 by shonakam          #+#    #+#             */
/*   Updated: 2025/02/08 23:13:38 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	handle_special_char_size(const char *line, size_t position)
{
	if (line[position] == '|')
		return (1);
	if (line[position] == '>')
	{
		if (line[position + 1] == '>')
			return (2);
		return (1);
	}
	if (line[position] == '<')
	{
		if (line[position + 1] == '<')
			return (2);
		return (1); 
	}
	return (0);
}

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

void	free_tokens(t_token **tokens)
{
	int	i;

	if (tokens == NULL)
		return;
	i = 0;
	while(tokens[i])
	{
		free(tokens[i]->word);
		free(tokens[i]);
		tokens[i++] = NULL;
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

e_tokentype	identify_metachar(const char *input, size_t pos)
{
	if (ft_strncmp(&input[pos], ">>", 2) == 0)
		return METACHAR_APPEND_REDIRECT;
	if (ft_strncmp(&input[pos], "<<", 2) == 0)
		return METACHAR_HEREDOC;
	if (ft_strncmp(&input[pos], "|", 1) == 0)
		return METACHAR_PIPE;
	if (ft_strncmp(&input[pos], "<",1) == 0)
		return METACHAR_INPUT_REDIRECT;
	if (ft_strncmp(&input[pos], ">", 1) == 0)
		return METACHAR_OUTPUT_REDIRECT;
	if (ft_strncmp(&input[pos], "'", 1) == 0)
		return METACHAR_SINGLE_QUOTE;
	if (ft_strncmp(&input[pos], "\"", 1) == 0)
		return METACHAR_DOUBLE_QUOTE;
	if (ft_strncmp(&input[pos], "$", 1) == 0)
		return METACHAR_DOLLAR;
	return METACHAR_NONE;
}
