/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 21:57:33 by shonakam          #+#    #+#             */
/*   Updated: 2025/02/18 19:54:59 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static int	check_value(char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '=' && s[i + 1])
			return (0);
		i++;
	}
	return (1);
}

int	cmd_env(int fd, t_envlist *envlist)
{
	char	**s;
	int		i;

	s = convert_to_envp(&envlist);
	if (!s)
		return (1);
	sort_envlist(s, get_listsize(&envlist), 0, 0);
	i = 0;
	while (s[i])
	{
		if (check_value(s[i]))
		{
			i++;
			continue ;
		}
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
