/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_split.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 19:09:27 by shonakam          #+#    #+#             */
/*   Updated: 2025/02/09 05:03:36 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static char	*remove_surrounding_quotes(const char *str)
{
	size_t		len;
	char		*result;

	if (!str || !*str)
		return (ft_strdup(""));
	len = ft_strlen(str);
	if ((str[0] == '"' && str[len - 1] == '"')
		|| (str[0] == '\'' && str[len - 1] == '\''))
	{
		result = (char *)ft_strndup(str + 1, len - 2);
		if (!result)
			return (NULL);
		return (result);
	}
	return (ft_strdup(str));
}

/* 
>> r[0]=key, r[1]=value
>> Split key and value by replacing '=' with '\0'
*/
char	**ft_split_by_eq(char *s)
{
	char	*eq;
	char	**r;

	eq = ft_strchr(s, '=');
	if (!eq)
		return (NULL);
	r = malloc(sizeof(char *) * 3);
	if (!r)
		return (NULL);
	*eq = '\0';
	r[0] = ft_strdup((const char *)s);
	r[1] = remove_surrounding_quotes((const char *)eq + 1);
	*eq = '=';
	r[2] = NULL;
	if (!r[0] || !r[1])
	{
		free(r[0]);
		free(r[1]);
		free(r);
		return (NULL);
	}
	return (r);
}
