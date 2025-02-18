/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoshker <kmoshker@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 00:31:06 by kmoshker          #+#    #+#             */
/*   Updated: 2023/11/02 19:07:21 by kmoshker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	charset(const char *c, const char *set)
{
	while (*set)
	{
		if (*c == *set)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*trimmed;
	char	*from_end;
	int		trimmed_len;

	if (!s1)
		return (NULL);
	if (!set)
		return (ft_strdup((char *)s1));
	while (*s1 && charset(s1, set))
		s1++;
	from_end = ft_strchr(s1, '\0') - 1;
	while (s1 < from_end && charset(from_end, set))
		from_end--;
	trimmed_len = from_end - s1 + 1;
	trimmed = (char *)malloc((trimmed_len + 1) * sizeof(char));
	if (!trimmed)
		return (NULL);
	ft_strlcpy(trimmed, s1, trimmed_len + 1);
	return (trimmed);
}
