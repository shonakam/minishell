/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   support.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 16:40:25 by shonakam          #+#    #+#             */
/*   Updated: 2024/09/07 01:40:36 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

char	*get_bin_path(t_envlist *list, char *cmd)
{
	char	**paths;
	char	*path = NULL;
	char	*r;
	int		i;

	paths = ft_split(ft_getenv(list, "PATH"), ':');
	if (!paths)
		return (NULL);
	r = NULL;
	i = 0;
	while (paths[i])
	{
		path = concat_vars(3, paths[i], "/", cmd);
		if (is_executable(path))
			r = path;
		free(paths[i++]);
	}
	return (free(paths), r);
}

void free_envlist(t_envlist **l)
{
	t_envlist *current;
	t_envlist *next;

	current = *l;
	while (current)
	{
		next = current->next;
		if (current->key)
			free(current->key);
		if (current->value)
			free(current->value);
		free(current);
		current = next;
	}
	*l = NULL;
}

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
