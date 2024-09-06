/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 16:22:13 by shonakam          #+#    #+#             */
/*   Updated: 2024/09/04 21:58:12 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

/* list = l, key = k, value = v */
static void	ft_setenv(t_envlist **l, const char *k, const char *v)
{
	t_envlist	*new_variable;

	new_variable = malloc(sizeof(t_envlist));
	if (!new_variable)
	{
		perror("ft_setenv: malloc for new_variable");
		return ;
	}
	new_variable->key = ft_strdup(k);
	new_variable->value = ft_strdup(v);
	if (!new_variable->key || !new_variable->value)
	{
		free(new_variable->key);
		free(new_variable->value);
		free(new_variable);
		perror("ft_setenv: malloc for [key|value]");
		return ;
	}
	new_variable->next = *l;
	*l = new_variable;
}

void	ft_putenv(t_envlist **l, const char *k, const char *v)
{
	t_envlist	*current;
	char		*tmp;

	current = *l;
	while (current)
	{
		if ((ft_strlen(current->key) == ft_strlen(k)) &&
			(ft_strncmp(current->key, k, ft_strlen(k)) == 0))
		{
			tmp = ft_strdup(v);
			if (!tmp)
			{
				perror("ft_putenv: malloc");
				return;
			}
			free(current->value);
			current->value = tmp;
			return ;
		}
		current = current->next;
	}
	ft_setenv(l, k, v);
}

void	ft_clearenv(t_envlist **list, char *key)
{
	t_envlist	*current;
	t_envlist	*prev;

	current = *list;
	prev = NULL;
	while (current)
	{
		if ((ft_strlen(current->key) == ft_strlen(key)) &&
			(ft_strncmp(current->key, key, ft_strlen(key)) == 0))
		{
			if (!prev)
				*list = current->next;
			else
				prev->next = current->next;
			return (free(current->key), free(current->value), free(current));
		}
		prev = current;
		current = current->next;
	}
}

char	*ft_getenv(t_envlist *list, char *key)
{
	while (list)
	{
		if ((ft_strlen(list->key) == ft_strlen(key)) &&
			(ft_strncmp(list->key, key, ft_strlen(key)) == 0))
			return list->value;
		list = list->next;
	}
	return (NULL);
}

t_envlist	*make_envlist(char **envp)
{
	t_envlist	*head;
	char		**kv;
	int	i;

	head = NULL;
	i = 0;
	while (envp[i])
	{
		kv = ft_split_by_eq(envp[i]);
		if (!kv)
		{
			perror("ft_split_by_eq");
			// return (NULL);
		}
		ft_putenv(&head, kv[0], kv[1]);
		free(kv[0]);
		free(kv[1]);
		free(kv);
		i++;
	}
	return (head);
}
