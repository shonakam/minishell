/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 18:23:42 by shonakam          #+#    #+#             */
/*   Updated: 2024/09/21 00:26:45 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	init_expand_state(t_state *state)
{
	state->result = ft_strdup("");
	if (!state->result)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	state->v = NULL;
	state->s = 0;
	state->e = 0;
	state->in_single = 0;
	state->in_double = 0;
}

char	*concat_and_free(char *result, char *tmp)
{
	char *new_result;

	if (!result)
		return (ft_strdup(tmp));
	new_result = ft_strjoin(result, tmp);
	free(result);
	free(tmp);
	return (new_result);
}

/* 
-- getpid() is forbidden
-- [0, #, @]
*/
char	*expand_special_variable(const char *str, int status)
{
	if (ft_strncmp(str, "$?", 2) == 0)
		return (ft_itoa(status));
	if (ft_strncmp(str, "$$", 2) == 0)
		return ("[PID]");
	return (NULL);
}

/* 1 == single, 2 == double */
void	state_toggle(t_state *state, int flag)
{
	if (flag == 1)
		state->in_single = !state->in_single;
	else if (flag == 2)
		state->in_double = !state->in_double;
}