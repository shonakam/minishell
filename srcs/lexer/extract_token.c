/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 05:32:02 by shonakam          #+#    #+#             */
/*   Updated: 2025/02/09 11:04:13 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static int	is_metachar(const char *line, size_t pos)
{
	if (line[pos] == '|')
		return (1);
	if (line[pos] == '>' || line[pos] == '<')
		return (1);
	return (0);
}

static void	set_size_and_type(const char *line, size_t pos,
	t_tokentype *type, size_t *token_size)
{
	if (line[pos] == '>' && line[pos + 1] == '>')
		*token_size = 2;
	else if (line[pos] == '<' && line[pos + 1] == '<')
		*token_size = 2;
	else
		*token_size = 1;
	*type = identify_metachar(line, pos);
}

void	extract_token(const char *line, t_token **toks, size_t pos, size_t c)
{	
	t_tokentype	type;
	size_t		token_size;

	while (line[pos])
	{
		while (line[pos] && ft_isspace(line[pos]))
			pos++;
		if (line[pos] == '\0')
			break ;
		if (is_metachar(line, pos))
			set_size_and_type(line, pos, &type, &token_size);
		else
		{
			token_size = get_token_size(line, pos);
			type = TOKEN_WORD;
		}
		toks[c++] = create_token(type, line, pos, token_size);
		pos += token_size;
	}
	toks[c] = NULL;
}
