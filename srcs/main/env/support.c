/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   support.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 16:40:25 by shonakam          #+#    #+#             */
/*   Updated: 2024/09/04 21:33:13 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	get_listsize(t_envlist **l)
{
	t_envlist	*current;
	int			size;

	current = *l;
	size = 0;
	while (current)
	{
		size++;
		current = current->next;
	}
	return (size);
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
	r[1] = ft_strdup((const char *)eq + 1);
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
