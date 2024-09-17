/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 04:06:16 by shonakam          #+#    #+#             */
/*   Updated: 2024/09/18 03:48:44 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

/*
-- $の分1進める
-- state->vに変数をdup
-- vのlenを取得しstate->sを進める
-- 取得できない場合はtrim
*/
static char	*expand_env(const char *in, t_state *state, t_envlist *e)
{
	char	*value;
	size_t	s;

	state->e += 1;
	s = state->e;
	while ((ft_isalnum(in[state->e]) || in[state->e] == '_'))
		state->e++;
	state->v = ft_strndup(in + s, (state->e - s));
	if(!state->v)
		return (perror("malloc"), NULL);
	value = ft_getenv(e, state->v);
	if (!value)
		return (free(state->v), ft_strdup(""));
	return (free(state->v), ft_strdup(value));
}

static int	expand_ptn(const char *in, t_state *state, int s, t_envlist *e)
{
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
		state->result = concat_and_free(state->result, state->v);
		free(state->v);
		state->s = state->e;
		return (1);
	}
	return (0);
}

/* 変数展開処理
-- 変数展開を行いながら文字列を連結する
-- $文字が来たらKEYと文字数を取得、$KEY分の文字をskip
-- ${VALUE}は考慮しない
*/
char	*expand_variables(const char *input, int status, t_envlist *e)
{
	t_state	state;

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
		state.result = concat_and_free(state.result,
			ft_strndup(input + state.s, (state.e - state.s)));
		state.s = state.e;
	}
	return (state.result);
}
