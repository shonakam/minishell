/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoshker <kmoshker@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 19:57:21 by kmoshker          #+#    #+#             */
/*   Updated: 2023/10/03 19:46:44 by kmoshker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*new;
	char	*new_2;

	if (!s)
		return (NULL);
	if (start >= ft_strlen(s) || len == 0)
	{
		new = (char *)malloc(1 * sizeof(char));
		if (!new)
			return (NULL);
		*new = '\0';
		return (new);
	}
	if (ft_strlen(s) < len)
		len = ft_strlen(s) - start;
	new = malloc((len + 1) * (sizeof(char)));
	if (!new)
		return (NULL);
	new_2 = new;
	while (len-- > 0 && s[start])
		*new_2++ = s[start++];
	*new_2 = '\0';
	return (new);
}
