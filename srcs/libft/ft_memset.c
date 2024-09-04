/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoshker <kmoshker@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 17:01:54 by kmoshker          #+#    #+#             */
/*   Updated: 2023/09/23 10:20:10 by kmoshker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *buf, int c, size_t len)
{
	unsigned char	*new;

	new = (unsigned char *)buf;
	while (len > 0)
	{
		*new = (unsigned char)c;
		len--;
		new++;
	}
	return (buf);
}
