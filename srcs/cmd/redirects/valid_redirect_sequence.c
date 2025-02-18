/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_redirect_sequence.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 17:06:04 by shonakam          #+#    #+#             */
/*   Updated: 2025/02/14 21:16:05 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static int	has_redirect_prefix(char *arg)
{
	size_t	len;

	len = ft_strlen(arg);
	if (len < 3)
		return (0);
	if (len == 2 && ft_strcmp(arg, ">>") == 0)
		return (1);
	else if (len == 1)
	{
		if (ft_strcmp(arg, ">") == 0 || ft_strcmp(arg, "<") == 0)
			return (1);
	}
	return (0);
}

/* verify if there is an even number of words */
int	valid_redirect_sequence(char **av)
{
	size_t	i;

	i = 0;
	while (av[i])
	{
		if (has_redirect_prefix(av[i]))
		{
			if (!(i % 2 == 0))
				return (1);
		}
		i++;
	}
	return (0);
}
