/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 21:57:33 by shonakam          #+#    #+#             */
/*   Updated: 2025/02/09 04:30:15 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	cmd_env(int fd, t_envlist *envlist)
{
	char	**s;
	int		i;

	s = convert_to_envp(&envlist);
	if (!s)
		return (1);
	i = 0;
	while (s[i])
	{
		ft_putstr_fd(s[i], fd);
		ft_putstr_fd("\n", fd);
		i++;
	}
	i = 0;
	while (s[i])
		free(s[i++]);
	free(s);
	return (0);
}
