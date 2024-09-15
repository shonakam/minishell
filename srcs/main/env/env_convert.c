/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_convert.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 19:20:41 by shonakam          #+#    #+#             */
/*   Updated: 2024/09/15 14:12:39 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static char	*set_envvar(char *k, char *v)
{
	char	*str;
	char	*tmp;

	str = malloc(sizeof(char) * (ft_strlen(k) + ft_strlen(v) + 2));
	if (!str)
		return (NULL);
	tmp = str;
	while (*k)
		*tmp++ = *k++;
	*tmp++ = '=';
	while (*v)
		*tmp++ = *v++;
	*tmp = '\0';
	return (str);
}

static void	free_envvar(char **r, int n)
{
	int	i;

	i = 0;
	while (i < n)
		free(r[i++]);
	free(r);
}

/* skip head -> not size+1  */
char	**convert_to_envp(t_envlist	**l)
{
	t_envlist	*current;
	char		**r;
	int			size;
	int			i;

	size = get_listsize(l);
	r = malloc(sizeof(char *) * (size));
	if (!r)
	{
		perror("convert_to_envp: malloc");
		return(NULL);
	}
	current = (*l)->next;
	i = 0;
	while (current)
	{
		r[i] = set_envvar(current->key, current->value);
		if (!r[i])
			return (free_envvar(r, i),
					perror("convert_to_envp: maloc for set_envvar"), NULL);
		current = current->next;
		i++;
	}
	r[i] = NULL;
	return (r);
}
