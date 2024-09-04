/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosh <mosh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 23:21:40 by kmoshker          #+#    #+#             */
/*   Updated: 2024/03/07 01:57:23 by mosh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat(char *dst, const char *src)
{
	int				num1;
	size_t			i;

	num1 = ft_strlen(dst);
	i = 0;
	while (src[i] != '\0')
	{
		dst[num1 + i] = src[i];
		i++;
	}
	dst[num1 + i] = '\0';
	return (dst);
}

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*new;
	int		len1;
	int		len2;

	if (!s1 && !s2)
		return (NULL);
	else if (!s1)
		return ((char *)s2);
	else if (!s2)
		return ((char *)s1);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	new = (char *)malloc((len1 + len2 + 1) * sizeof(char));
	if (!new)
		return (NULL);
	ft_strcpy(new, s1);
	ft_strcat(new, s2);
	return (new);
}
