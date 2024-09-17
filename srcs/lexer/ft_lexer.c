/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 22:25:51 by shonakam          #+#    #+#             */
/*   Updated: 2024/09/17 02:04:01 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static t_token	*create_token(TokenType t, const char *l, size_t p, size_t s)
{
	t_token	*tok;

	tok = (t_token *)malloc(sizeof(t_token));
	if (!tok)
		return (NULL);
	tok->type = t;
	tok->word	= ft_substr(l, p, s);
	return (tok);
}


static size_t	get_token_size(const char *line, size_t posision, int flag)
{
	size_t	end;

	end = posision;
	if (line[posision] == '$')
	{
		end++;
		while (line[end] && (ft_isalnum(line[end]) || line[end] == '_'))
			end++;
		return (end - posision);
	}
	while (flag == 0 && line[end] && !ft_isspace(line[end]))
	{
		end++;
		if (line[end] == '|')
			break ;
	}
	while (flag == 1 && line[end] && line[end] != '\'')
		end++;
	while (flag == 2 && line[end] && line[end] != '"')
		end++;
	return (end - posision);
}

size_t	size_matcher(TokenType type, const char *line, size_t pos)
{
	if (type == METACHAR_SINGLE_QUOTE)
		return (2 + get_token_size(line, pos + 1, 1));
	else if (type == METACHAR_DOUBLE_QUOTE)
		return (2 + get_token_size(line, pos + 1, 2));
	else if (type == METACHAR_NONE)
		return (get_token_size(line, pos, 0));
	else if (type == METACHAR_DOLLAR)
	{
		if (line[pos + 1] == '$' || line[pos + 1] == '?')
			return (2);
		else
			return (get_token_size(line, pos, 0));
	}
	else if (type == 4 || type == 2 || type == 3 || type == 1 || type == 5)
		return (2u);
	else
		return (1u);
}

void	extract_token(const char *line, t_token **toks, size_t pos, size_t c)
{	
	TokenType	type;
	size_t		token_size;

	while (line[pos] && ft_isspace(line[pos]))
		pos++;
	if (line[pos] == '\0')
	{
		toks[c] = NULL;
		return ;
	}
	type = identify_metachar(line, pos);
	token_size = 0u;
	token_size = size_matcher(type, line, pos);
	toks[c] = create_token(type, line, pos, token_size);
	pos += token_size;
	extract_token(line, toks, pos, ++c);
}

t_token	**ft_lexer(char *line)
{
	t_token	**tokens;

	add_history(line);
	line = resolve_eos(line);
	if (!line)
		return (NULL);
	if (strlen(line) > 0)
		add_history(line); // rl_replace_line
	tokens = (t_token **)malloc(ARGUMENT_SIZE * sizeof(t_token *));
	if (!tokens)
		return (NULL);
	extract_token(line, tokens, 0, 0);
	tokens = check_unexpected_token(tokens);
	return (free(line), tokens);
}
