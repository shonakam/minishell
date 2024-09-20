/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rm_quote.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 06:48:07 by shonakam          #+#    #+#             */
/*   Updated: 2024/09/19 21:29:25 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static void	rm_pattern(const char *input, t_state *state, char c, int mode)
{
	state_toggle(state, mode);
	state->s++;
	while (input[state->s] && input[state->s] != c)
		state->result = concat_and_free(
			state->result, ft_strndup(&input[state->s++], 1));
	if (input[state->s] == c)
	{
		state_toggle(state, mode);
		state->s++;
	}
	else
	{
		// 終了クオートが見つからない場合のエラーハンドリング
		ft_putendl_fd("Error: Unclosed quote found", STDERR_FILENO);
		// クリーンアップと終了などしたい
	}
}

char	*remove_quotes(const char *input)
{
	t_state state;

	init_expand_state(&state);
	while (input[state.s])
	{
		if (input[state.s] == '\'' && !state.in_double)
			rm_pattern(input, &state, '\'', 1);
		else if (input[state.s] == '"' && !state.in_single)
			rm_pattern(input, &state, '"', 2);
		else
			state.result = concat_and_free(state.result, ft_strndup(&input[state.s++], 1));
	}
	return (state.result);
}
