/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_context.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 18:23:31 by shonakam          #+#    #+#             */
/*   Updated: 2025/02/18 17:41:50 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static int	resolve_newline(t_token *token)
{
	if (token->type == METACHAR_PIPE
		|| token->type == METACHAR_AND
		|| token->type == METACHAR_INPUT_REDIRECT
		|| token->type == METACHAR_OUTPUT_REDIRECT
		|| token->type == METACHAR_HEREDOC
		|| token->type == METACHAR_APPEND_REDIRECT)
	{
		print_syntax_error("newline");
		return (1);
	}
	return (0);
}

static int	comp_with_next(t_token *t1, t_token *t2)
{
	if (t1 == METACHAR_NONE)
		return (0);
	if (is_redirects(t1->type) && is_metachar(t2->type))
	{
		print_syntax_error(t2->word);
		return (SYNTAX_ERRNO);
	}
	return (0);
}

static int	handle_only_metachar(t_token **tokens)
{
	if (!tokens || !*tokens)
		return (1);
	if (is_pipe_or_and(tokens[0]->type))
	{
		print_syntax_error(tokens[0]->word);
		return (1);
	}
	else if (is_redirects(tokens[0]->type))
	{
		if (tokens[0]->type == METACHAR_HEREDOC)
			return (0);
		resolve_newline(tokens[0]);
		return (1);
	}
	return (0);
}

int	valid_context(t_token **tokens)
{
	int		have_quote;
	int		status;
	size_t	i;

	if (handle_only_metachar(tokens))
		return (SYNTAX_ERRNO);
	have_quote = 0;
	i = 0;
	while (tokens[i])
	{
		have_quote = find_quotes(tokens[i]->word);
		if (!have_quote && tokens[i + 1])
		{
			status = comp_with_next(tokens[i], tokens[i + 1]);
			if (status == SYNTAX_ERRNO)
				return (SYNTAX_ERRNO);
		}
		i++;
	}
	if (!tokens[i] && i > 0 && resolve_newline(tokens[i - 1]))
		return (SYNTAX_ERRNO);
	return (0);
}
