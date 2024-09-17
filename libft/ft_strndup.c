/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 18:45:53 by shonakam          #+#    #+#             */
/*   Updated: 2024/09/16 18:52:56 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *src, size_t n)
{
	char	*dest;
	size_t	len;
	size_t	i;

	len = 0;
	while (src[len] && len < n)
		len++;
	dest = (char *)malloc(sizeof(char) * (len + 1));
	if (!dest)
		return (NULL);
	i = 0;
	while (i < len)
	{
		dest[i] = src[i];
		i++;
	}
	dest[len] = '\0';
	return (dest);
}
// int main(void)
// {
// 	const char *original = "Hello, world!";
// 	char *dup = ft_strndup(original, 5);

// 	printf("Original: %s\n", original);
// 	printf("Duplicated: %s\n", dup);

// 	free(dup);  // メモリの解放
// 	return 0;
// }
