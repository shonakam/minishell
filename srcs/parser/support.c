/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   support.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 03:38:04 by shonakam          #+#    #+#             */
/*   Updated: 2024/09/05 04:26:59 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	cpy_args(t_command *cmd, char **a)
{
	int	i;

	i = 0;
	while (cmd->argv[i])
	{
		a[i] = ft_strdup(cmd->argv[i]);
		if (!a[i])
		{
			perror("cpy_args: strdup");
			while (i > 0)
				free(a[--i]);
			free(a);
			return;
		}
		i++;
	}
	i = 0;
	while (cmd->argv[i])
		free(cmd->argv[i++]);
	free(cmd->argv);
}
