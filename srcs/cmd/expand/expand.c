/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 04:06:16 by shonakam          #+#    #+#             */
/*   Updated: 2025/02/14 21:35:57 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static char	*expand_env(const char *in, t_state *state, t_envlist *e)
{
	char	*value;
	size_t	s;

	state->e += 1;
	s = state->e;
	while ((ft_isalnum(in[state->e]) || in[state->e] == '_'))
		state->e++;
	state->v = ft_strndup(in + s, (state->e - s));
	if (!state->v)
		return (print_syscall_error("malloc: expand_env", ENOMEM), NULL);
	value = ft_getenv(e, state->v);
	if (!value)
		return (free(state->v), ft_strdup(""));
	return (free(state->v), ft_strdup(value));
}

static int	expand_ptn(const char *in, t_state *state, int s, t_envlist *e)
{
	if (in[state->e + 1] == '\0')
		return (0);
	state->v = expand_special_variable(in + state->e, s);
	if (state->v)
	{
		state->result = concat_and_free(state->result, state->v);
		state->e += 2;
		state->s = state->e;
		return (1);
	}
	else
	{
		state->v = expand_env(in, state, e);
		if (state->v)
			state->result = concat_and_free(state->result, state->v);
		state->s = state->e;
		return (1);
	}
	return (0);
}

char	*expand_variables(const char *input, int status, t_envlist *e)
{
	t_state	state;
	char	*result;
	char	*tmp;

	init_expand_state(&state);
	while (input[state.s])
	{
		if (input[state.s] == '\'' && !state.in_double)
			state_toggle(&state, 1);
		else if (input[state.s] == '"' && !state.in_single)
			state_toggle(&state, 2);
		if (input[state.e] == '$' && !state.in_single)
		{
			if (expand_ptn(input, &state, status, e))
				continue ;
		}
		state.e++;
		tmp = ft_strndup(input + state.s, (state.e - state.s));
		if (tmp)
			state.result = concat_and_free(state.result, tmp);
		state.s = state.e;
	}
	result = state.result;
	return (result);
}
