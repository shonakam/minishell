/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   support.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 21:39:37 by shonakam          #+#    #+#             */
/*   Updated: 2024/09/07 02:55:15 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	count_pipe(t_token **tokens)
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

void	close_pipefds(int *pipe_fds, int n)
{
	int	i;

	i = 0;
	while (i < n)
		close(pipe_fds[i++]);
	free(pipe_fds);
}
