/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   support.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 21:39:37 by shonakam          #+#    #+#             */
/*   Updated: 2024/09/01 23:09:52 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	count_pipechar(t_token **tokens)
{
	int	i;

	i = 0;
	while (*tokens)
	{
		if ((*tokens)->type == METACHAR_PIPE)
			i++;
		tokens++;
	}
	return (i);
}
