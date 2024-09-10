/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoshker <kmoshker@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 17:40:39 by kmoshker          #+#    #+#             */
/*   Updated: 2023/10/03 19:43:12 by kmoshker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
// {
// 	size_t	start;
// 	size_t	len_needle;

// 	// if (!haystack && !len)
// 	// 	return (NULL);
// 	len_needle = ft_strlen(needle);
// 	start = 0;
// 	if (!*needle)
// 		return ((char *) haystack);
// 	if (!len)
// 		return (NULL);
// 	while (start < len && haystack[start])
// 	{
// 		if (!ft_strncmp(&haystack[start], needle, len_needle))
// 			return ((char *)(haystack + start));
// 		start++;
// 	}
// 	return (NULL);
// }

// char	*ft_strnstr(const char *str,const char *to_find, size_t len)
// {
// 	size_t	i;
// 	size_t	j;

// 	if (!*to_find)
// 		return ((char *)str);
	// if (!len)
	// 	return (NULL);
// 	while (*str)
// 	{
// 		i = 0;
// 		j = 0;
// 		while (to_find[i] && str[j] && to_find[i] == str[j] && i < len)
// 		{
// 			i++;
// 			j++;
// 		}
// 		if (i == len)
// 			return ((char *)str);
// 		str++;
// 	}
// 	return (0);
// }
char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	needle_len;

	if (!*needle)
		return ((char *)haystack);
	if (!len)
		return (NULL);
	needle_len = ft_strlen(needle);
	while (*haystack && len-- >= needle_len)
	{
		if (*haystack == *needle && !ft_strncmp(haystack, needle, needle_len))
			return ((char *)haystack);
		haystack++;
	}
	return (NULL);
}

// int main(void)
// {
// 	char	*s1 = "FF";
// 	char	*s2 = "see F your F return F now F";
// 	size_t	max = strlen(s2);
// 	char	*i1 = strnstr(s2, s1, max); 
// 	char	*i2 = ft_strnstr(s2, s1, max);

// 	if (i1)
// 	{
// 		while (*i1)
// 		{
// 			printf("strnstr: %c\n", *i1);
// 			i1++;
// 		}
// 	}
// 	else
// 	{
// 		printf("strnstr: Not Found\n");
// 	}

// 	if (i2)
// 	{
// 		while (*i2)
// 		{
// 			printf("ft_strnstr: %c\n", *i2);
// 			i2++;
// 		}
// 	}
// 	else
// 	{
// 		printf("ft_strnstr: Not Found\n");
// 	}

// 	return (0);
// }
