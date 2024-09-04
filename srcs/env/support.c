/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   support.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 16:40:25 by shonakam          #+#    #+#             */
/*   Updated: 2024/09/04 18:48:37 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

// int	check_null_envlist_member(t_envlist *l)
// {
// 	int	flag;

// 	flag = 0;
// 	if (!l->key && l->value)
// 	{
// 		free(l->value);
// 		flag++;
// 	}
// 	else if (l->key && !l->value)
// 	{
// 		free(l->key);
// 		flag++;
// 	}
// 	else if (!l->key && !l->value)
// 		flag++;
// 	return (flag);
// }

// static int	check_null_duplicate(char **s)
// {
// 	int	flag;

// 	flag = 0;
// 	if (!s[0] && s[1])
// 	{
// 		free(s[1]);
// 		flag++;
// 	}
// 	else if (s[0] && !s[1])
// 	{
// 		free(s[0]);
// 		flag++;
// 	}
// 	else if (!s[0] && !s[1])
// 		flag++;
// 	return (flag);
// }

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
	r[1] = ft_strdup((const char *)eq + 1);
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
