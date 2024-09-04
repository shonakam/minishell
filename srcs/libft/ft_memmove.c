/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoshker <kmoshker@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 20:10:41 by kmoshker          #+#    #+#             */
/*   Updated: 2023/10/03 19:37:37 by kmoshker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t len)
{
	unsigned char	*dest_c;
	unsigned char	*src_c;

	dest_c = (unsigned char *)dest;
	src_c = (unsigned char *)src;
	if (!dest && !src)
		return (NULL);
	if (dest_c <= src_c)
	{
		while (len--)
		{
			*dest_c++ = *src_c++;
		}
	}
	else
	{
		dest_c += len;
		src_c += len;
		while (len--)
		{
			*(--dest_c) = *(--src_c);
		}
	}
	return ((void *)dest);
}
