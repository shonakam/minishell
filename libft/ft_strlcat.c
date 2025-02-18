/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoshker <kmoshker@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 16:50:13 by kmoshker          #+#    #+#             */
/*   Updated: 2023/09/29 16:35:00 by kmoshker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	dst_num;
	size_t	src_num;

	if (!dst && size == 0)
		return (ft_strlen(src));
	dst_num = 0;
	while (dst[dst_num] != '\0' && dst_num < size)
		dst_num++;
	src_num = ft_strlen(src);
	if (size <= dst_num)
		return (size + src_num);
	i = 0;
	while (src[i] != '\0' && i < size - dst_num - 1)
	{
		dst[dst_num + i] = src[i];
		i++;
	}
	if (dst_num < size)
		dst[dst_num + i] = '\0';
	return (dst_num + src_num);
}
