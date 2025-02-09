/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 22:25:51 by shonakam          #+#    #+#             */
/*   Updated: 2025/02/09 05:48:41 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

t_token	*create_token(t_tokentype t, const char *l, size_t p, size_t s)
{
	t_token	*tok;

	tok = (t_token *)malloc(sizeof(t_token));
	if (!tok)
		return (NULL);
	tok->type = t;
	tok->word = ft_substr(l, p, s);
	return (tok);
}

size_t	get_token_size(const char *line, size_t position)
{
	size_t	end;
	char	quote_char;
	int		in_quotes;

	end = position;
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
	return (end - position);
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
	if (line && strlen(line) > 0)
		rl_replace_line(line, 1);
	tokens = (t_token **)malloc(ARGUMENT_SIZE * sizeof(t_token *));
	if (!tokens)
		return (NULL);
	extract_token(line, tokens, 0, 0);
	tokens = check_unexpected_token(tokens);
	return (free(line), tokens);
}
