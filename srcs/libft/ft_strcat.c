/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoshker <kmoshker@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 20:55:27 by kmoshker          #+#    #+#             */
/*   Updated: 2024/03/06 20:55:52 by kmoshker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat(char *dst, const char *src)
{
	int	num1;
	int	i;

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
