/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strspn.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 17:09:56 by shonakam          #+#    #+#             */
/*   Updated: 2025/02/09 04:21:34 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strspn(const char *s, const char *accept)
{
	size_t		i;
	int			j;
	int			match;

	if (!s || !accept)
		return (0);
	i = 0;
	while (s[i])
	{
		match = 0;
		j = 0;
		while (accept[j])
		{
			if (s[i] == accept[j])
			{
				match = 1;
				break ;
			}
			j++;
		}
		if (!match)
			break ;
		i++;
	}
	return (i);
}
