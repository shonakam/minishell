/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_quoted.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 04:06:16 by shonakam          #+#    #+#             */
/*   Updated: 2024/09/18 01:57:19 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "includes/minishell.h"

char *get_env_var(const char *name)
{
	if (strcmp(name, "USER") == 0) {
		return "guest";
	} else if (strcmp(name, "HOME") == 0) {
		return "/home/guest";
	}
	return "";
}

char*	concat_and_free(char *result, char *tmp)
{
	char *new_result;

	if (!result)
		return (ft_strdup(tmp));
	new_result = ft_strjoin(result, tmp);
	free(result);
	return (new_result);
}
/*
-- $の分1進める
-- state->vに変数をdup
-- vのlenを取得しstate->sを進める
-- 取得できない場合はtrim
*/
char	*expand_env(const char *input, t_state *state)
{
	char	*value;
	size_t	s;

	// printf("input[c]: %c\n", input[state->e]);
	state->e += 1;
	s = state->e;
	while ((ft_isalnum(input[state->e]) || input[state->e] == '_'))
		state->e++;
	state->v = ft_strndup(input + s, (state->e - s));
	printf("state->v: %s\n", state->v);
	if(!state->v)
		return (perror("malloc"), NULL);
	value = get_env_var(state->v);
	if (!value)
		return (free(state->v), ft_strdup(""));
	return (free(state->v), ft_strdup(value));
}

// 変数展開処理
char	*expand_variables(const char *input, int status)
{
	t_state	state;

	init_expand_state(&state);
	while (input[state.s])
	{
		if (input[state.s] == '\'' && !state.in_double)
			state_toggle(&state, 1);
		else if (input[state.s] == '"' && !state.in_single)
			state_toggle(&state, 2);
		if (input[state.e])
		{
			if ((state.in_single && input[state.e] == '\'') ||
				(state.in_double &&  input[state.e] == '"'))
				break ;
			if (input[state.e] == '$' && !state.in_single)
			{
				state.v = expand_special_variable(input + state.e, status);
				if (state.v)
				{
					state.result = concat_and_free(state.result, state.v);
					state.e += 2;
					state.s = state.e;
					continue ;
				}
				else
				{
					state.v = expand_env(input, &state);
					state.result = concat_and_free(state.result, state.v);
					free(state.v);
					state.s = state.e;
					continue ;
				}
			}
			state.e++;
		}
		state.result = concat_and_free(state.result, ft_strndup(input + state.s, (state.e - state.s)));
		state.s = state.e;
	}
	return (state.result);
}

/*
-- 変数展開を行いながら文字列を連結する
-- $文字が来たらKEYと文字数を取得、$KEY分の文字をskip
-- ${VALUE}は考慮しない
*/
int main()
{
	const char *input0 = "\"Hello \"$USER\", your home is '$HOME'\"";
    const char *input1 = "Hello \"$USER\", your home is '$HOME'";
	const char *input2 = "\'hello\"$USER\"WORLD\'";
	const char *input3 = "$USER";
	const char *input4 = "HELLO";
	const char *input5 = "$$$?";
	const char *input = "Hello ${USER}, your home is ${HOME}/docs";
    char *output = expand_variables(input0, 127);
	printf("Input: %s\n", input0);
    printf("Output: %s\n", output);
    free(output);
}

