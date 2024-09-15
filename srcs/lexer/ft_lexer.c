/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 22:25:51 by shonakam          #+#    #+#             */
/*   Updated: 2024/09/15 18:15:49 by shonakam         ###   ########.fr       */
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

static TokenType identify_metachar(const char *input, size_t pos)
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
	if (ft_strncmp(&input[pos], "$?", 2) == 0)
		return METACHAR_EXIT_STATUS;
	if (ft_strncmp(&input[pos], "$", 1) == 0)
		return METACHAR_DOLLAR;
	return METACHAR_NONE;
}

static size_t	get_token_size(const char *line, size_t posision, int flag)
{
	size_t	end;

	end = posision;
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
	if (type == METACHAR_SINGLE_QUOTE)
		token_size = (2 + get_token_size(line, (pos + 1), 1));
	else if (type == METACHAR_DOUBLE_QUOTE)
		token_size = (2 + get_token_size(line, (pos + 1), 2));
	else if (type == METACHAR_NONE)
		token_size = get_token_size(line, pos, 0);
	else if (type == 4 || type == 5 || type == 10)
		token_size = 2u;
	else if (type == 1 || type == 2 || type == 3 || type == 8)
		token_size = 1u;
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
