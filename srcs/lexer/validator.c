/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 11:30:12 by shonakam          #+#    #+#             */
/*   Updated: 2025/02/12 21:36:43 by shonakam         ###   ########.fr       */
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

static int	token_matcher(t_token **t, int i)
{
	if (t[i]->type == METACHAR_PIPE &&
		t[i + 1] && t[i + 1]->type == METACHAR_PIPE)
	{
		ft_putendl_fd("minishell: unsupported syntax `||\"", STDERR_FILENO);
		return (1);
	}
	if (t[i]->type == METACHAR_AND &&
		t[i + 1] && t[i + 1]->type == METACHAR_AND)
	{
		ft_putendl_fd("minishell: unsupported syntax `&&\"", STDERR_FILENO);
		return (1);
	}
	else if ((i == 0
		&& (t[i]->type == METACHAR_PIPE || t[i]->type == METACHAR_AND))
		|| (i > 0
		&& ((t[i]->type == METACHAR_PIPE && t[i-1]->type != METACHAR_NONE)
		|| (t[i]->type == METACHAR_AND && t[i-1]->type != METACHAR_NONE))))
	{
		return (print_syntax_error(t[i]->word), SYNTAX_ERRNO);
	}
	return (0);
}

static int	find_quotes(const char *token)
{
	while (*token)
	{
		if (*token == '\'' || *token == '\"')
			return (1);
		token++;
	}
	return (0);
}

int	validate_tokens(t_token **tokens)
{
	int	have_quote;
	int	i;


	have_quote = 0;
	i = 0;
	while (tokens[i])
	{
		have_quote = find_quotes(tokens[i]->word);
		if (!have_quote && token_matcher(tokens, i))
			return (SYNTAX_ERRNO);
		i++;
		if (!tokens[i] && index > 0 && resolve_newline(tokens[i - 1]))
			return (SYNTAX_ERRNO);
	}
	return (0);
}
