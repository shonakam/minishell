/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 22:25:51 by shonakam          #+#    #+#             */
/*   Updated: 2024/09/18 23:05:04 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static size_t	handle_dollar(const char *line, size_t pos)
{
	size_t	end;

	end = pos + 1;
	// if (line[end] == '?' || line[end] == '$')
	// 	return (2);
	while (line[end] && (ft_isalnum(line[end])
		|| line[end] == '_' || line[end] == '?' || line[end] == '$'))
		end++;
	return (end - pos);
}

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
/*
-- Handle special characters (|, >, >>, <, <<)
*/
static size_t	get_token_size(const char *line, size_t position, int flag)
{
	size_t	end;
	char	quote_char;

	end = position;
	if (line[position] == '$')
		return (handle_dollar(line, position));
	if (flag == 1)
		quote_char = '\'';
	else if (flag == 2)
		quote_char = '"';
	if (flag == 1 || flag == 2)
	{
		end++;
		while (line[end] && line[end] != quote_char)
			end++;
		if (line[end] == quote_char)
			end++;
		return (end - position);
	}
	if (handle_special_char_size(line, position))
		return (handle_special_char_size(line, position));
	while (line[end] && !ft_isspace(line[end])
		&& line[end] != '|' && line[end] != '>' && line[end] != '<')
		end++;
	return (end - position);
}

void	extract_token(const char *line, t_token **toks, size_t pos, size_t c)
{	
	TokenType	type;
	size_t		token_size;
	int flag;

	// printf(">> %c\n", line[pos]);
	while (line[pos] && ft_isspace(line[pos]))
		pos++;
	if (line[pos] == '\0')
	{
		toks[c] = NULL;
		return ;
	}
	type = identify_metachar(line, pos);
	if (type == METACHAR_SINGLE_QUOTE)
		flag = 1;
	else if (type == METACHAR_DOUBLE_QUOTE)
		flag = 2;
	else
		flag = 0;
	token_size = get_token_size(line, pos, flag);
	toks[c] = create_token(type, line, pos, token_size);
	pos += token_size;
	extract_token(line, toks, pos, ++c);
}

t_token	**ft_lexer(char *line)
{
	t_token	**tokens;

	add_history(line);
	if (!valid_quote(line))
	{
		errno = EINVAL;
		perror("minishell");
		return (NULL);
	}
	line = resolve_eos(line);
	if (!line)
		return (NULL);
	if (strlen(line) > 0)
		add_history(line); // rl_replace_line
	tokens = (t_token **)malloc(ARGUMENT_SIZE * sizeof(t_token *));
	if (!tokens)
		return (NULL);
	extract_token(line, tokens, 0, 0); // <- segf
	// printf("\033[31mBREAKPOINT\033[0m\n");
	tokens = check_unexpected_token(tokens);
	return (free(line), tokens);
}
