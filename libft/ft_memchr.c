/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoshker <kmoshker@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 17:14:27 by kmoshker          #+#    #+#             */
/*   Updated: 2023/09/25 04:19:36 by kmoshker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*new;
	unsigned char	ch;

	ch = (unsigned char)c;
	new = (unsigned char *)s;
	while (n > 0)
	{
		if (*new == ch)
			return ((void *)new);
		new++;
		n--;
	}
	return (NULL);
}
