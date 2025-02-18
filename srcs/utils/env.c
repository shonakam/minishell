/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 16:40:25 by shonakam          #+#    #+#             */
/*   Updated: 2025/02/18 19:55:07 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	sort_envlist(char **arr, size_t size, size_t i, size_t j)
{
	char	*tmp;

	while (i < size - 1)
	{
		j = 0;
		while (j < size - i - 2)
		{
			if (ft_strcmp(arr[j], arr[j + 1]) > 0)
			{
				tmp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
}

t_envlist	*create_head_node(void)
{
	t_envlist	*head;

	head = malloc(sizeof(t_envlist));
	if (!head)
	{
		perror("create_head_node: malloc");
		return (NULL);
	}
	head->key = NULL;
	head->value = NULL;
	head->next = NULL;
	return (head);
}

int	is_valid_key(const char *key)
{
	size_t	i;

	if (!key || !key[0])
		return (0);
	if (!ft_isascii(key[0]) || !(ft_isalpha(key[0]) || key[0] == '_'))
		return (0);
	i = 1;
	while (key[i] != '\0')
	{
		if (!ft_isascii(key[i]) || !(ft_isalnum(key[i]) || key[i] == '_'))
			return (0);
		i++;
	}
	return (1);
}

void	free_envlist(t_envlist **l)
{
	t_envlist	*current;
	t_envlist	*next;

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
