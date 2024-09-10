/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoshker <kmoshker@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 20:26:17 by kmoshker          #+#    #+#             */
/*   Updated: 2023/09/25 02:12:06 by kmoshker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t len)
{
	unsigned char	*dest_c;
	unsigned char	*src_c;

	dest_c = (unsigned char *)dest;
	src_c = (unsigned char *)src;
	if (!dest && !src)
		return (NULL);
	while (len > 0)
	{
		*dest_c = *src_c;
		dest_c++;
		src_c++;
		len--;
	}
	return (dest);
}

// #include <stdio.h>
// #include <string.h>

// int main(void)
// {
//     char data[50] = "Hello, World!";

//     // Using memcpy with overlapping memory
//     printf("Before memcpy: %s\n", data);
//     memcpy(data + 5, data, 20); // これはオーバーラップしています！
//     printf("After memcpy: %s\n", data);

//     strcpy(data, "Hello, World!"); // データをリセット

//     // Using memmove with overlapping memory
//     printf("\nBefore memmove: %s\n", data);
//     memmove(data + 5, data, 20); // memmoveはオーバーラップに対応しています
//     printf("After memmove: %s\n", data);

//     return 0;
// }