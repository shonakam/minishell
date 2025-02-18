/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 11:29:44 by shonakam          #+#    #+#             */
/*   Updated: 2025/02/14 18:40:41 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static t_token	*create_token(
	t_tokentype type, const char *line, size_t pos, size_t size)
{
	t_token	*tok;

	tok = (t_token *)malloc(sizeof(t_token));
	if (!tok)
		return (NULL);
	tok->type = type;
	tok->word = ft_substr(line, pos, size);
	return (tok);
}

/* NORMARL WORD IS METACHAR_NONE */
static t_tokentype	identify_metachar(const char *input, size_t pos)
{
	if (input[pos] == '>' && input[pos + 1] && input[pos + 1] == '>')
		return (METACHAR_APPEND_REDIRECT);
	if (input[pos] == '<' && input[pos + 1] && input[pos + 1] == '<')
		return (METACHAR_HEREDOC);
	if (input[pos] == '|')
		return (METACHAR_PIPE);
	if (input[pos] == '<')
		return (METACHAR_INPUT_REDIRECT);
	if (input[pos] == '>')
		return (METACHAR_OUTPUT_REDIRECT);
	if (input[pos] == '\'')
		return (METACHAR_SINGLE_QUOTE);
	if (input[pos] == '"')
		return (METACHAR_DOUBLE_QUOTE);
	if (input[pos] == '$')
		return (METACHAR_DOLLAR);
	if (input[pos] == '&')
		return (METACHAR_AND);
	return (METACHAR_NONE);
}

static size_t	get_metachar_size(t_tokentype type)
{
	if (type == METACHAR_APPEND_REDIRECT || type == METACHAR_HEREDOC)
		return (2);
	if (type == METACHAR_PIPE
		|| type == METACHAR_AND
		|| type == METACHAR_INPUT_REDIRECT
		|| type == METACHAR_OUTPUT_REDIRECT)
		return (1);
	return (0);
}

static size_t	get_token_size(const char *line, size_t pos)
{
	size_t	end;
	char	quote_char;
	int		in_quotes;

	end = pos;
	quote_char = 0;
	in_quotes = 0;
	while (line[end])
	{
		if ((line[end] == '\'' || line[end] == '"') && in_quotes == 0)
		{
			in_quotes = 1;
			quote_char = line[end];
		}
		else if (line[end] == quote_char && in_quotes == 1)
		{
			in_quotes = 0;
			quote_char = 0;
		}
		else if (!in_quotes && (ft_isspace(line[end]) || line[end] == '|'
				|| line[end] == '>' || line[end] == '<'))
			break ;
		end++;
	}
	return (end - pos);
}

void	tokenizer(t_token **toks, char *line, size_t pos, size_t index)
{
	t_tokentype	type;
	size_t		size;

	while (line[pos])
	{
		while (line[pos] && ft_isspace(line[pos]))
			pos++;
		if (!line[pos])
			break ;
		type = identify_metachar(line, pos);
		size = get_metachar_size(type);
		if (size == 0)
			size = get_token_size(line, pos);
		toks[index++] = create_token(type, line, pos, size);
		pos += size;
	}
	toks[index] = NULL;
}
