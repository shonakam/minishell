/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   support.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 19:36:13 by shonakam          #+#    #+#             */
/*   Updated: 2025/02/14 19:53:21 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	is_metachar(t_tokentype t)
{
	if (t >= METACHAR_PIPE && t <= METACHAR_AND)
		return (1);
	return (0);
}

int	is_pipe_or_and(t_tokentype t)
{
	if (t == METACHAR_PIPE || t == METACHAR_AND)
		return (1);
	return (0);
}

int	is_redirects(t_tokentype t)
{
	if (t == METACHAR_OUTPUT_REDIRECT || t == METACHAR_INPUT_REDIRECT
		|| t == METACHAR_APPEND_REDIRECT || t == METACHAR_HEREDOC)
		return (1);
	return (0);
}
