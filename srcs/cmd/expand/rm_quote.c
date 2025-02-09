/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rm_quote.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 06:48:07 by shonakam          #+#    #+#             */
/*   Updated: 2025/02/09 04:36:50 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static void	rm_pattern(const char *input, t_state *state, char quote, int mode)
{
	state_toggle(state, mode);
	state->s++;
	while (input[state->s] && input[state->s] != quote)
	{
		state->result = concat_and_free(
				state->result, ft_strndup(&input[state->s++], 1));
	}
	if (input[state->s] == quote)
	{
		state_toggle(state, mode);
		state->s++;
	}
}

static void	resolve_space(t_state *state,
		const char *input, int *in_word, int f)
{
	if (f)
	{
		if (state->result && *in_word)
			state->result = concat_and_free(state->result, ft_strdup(" "));
		*in_word = 0;
		state->s++;
	}
	else
	{
		state->result = concat_and_free(state->result,
				ft_strndup(&input[state->s++], 1));
		*in_word = 1;
	}
}

char	*remove_quotes(const char *input)
{
	t_state		state;
	int			in_word;

	in_word = 0;
	init_expand_state(&state);
	while (input[state.s])
	{
		if (input[state.s] == '\'' && !state.in_double)
			rm_pattern(input, &state, '\'', 1);
		else if (input[state.s] == '"' && !state.in_single)
			rm_pattern(input, &state, '"', 2);
		else
			resolve_space(&state, input, &in_word,
				ft_isspace((unsigned char)input[state.s]));
	}
	return (state.result);
}
