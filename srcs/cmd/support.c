/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   support.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 21:39:37 by shonakam          #+#    #+#             */
/*   Updated: 2024/09/06 17:19:32 by shonakam         ###   ########.fr       */
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

int is_executable(const char *path)
{
	if (access(path, F_OK) != 0)
		return 0;
	if (access(path, X_OK) != 0)
		return 0;
	return 1;
}
