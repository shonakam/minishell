#include "../session_internal.h"

t_env	*env_new(char *key, char *value, bool has_value)
{
	t_env	*node;

	node = (t_env *)x_calloc(1, sizeof(t_env));
	if (!node)
		return (NULL);
	node->key = key;
	node->value = value;
	node->has_value = has_value;
	return (node);
}

void	env_free(void *content)
{
	t_env	*node;

	if (!content)
		return ;
	node = (t_env *)content;
	if (node->key)
		free(node->key);
	if (node->has_value && node->value)
		free(node->value);
	free(node);
}

// skip headnode
t_env	*env_find(t_list *lst, char *target)
{
	t_env	*content;
	size_t	n;

	if (!lst || !target)
		return (NULL);
	n = ft_strlen(target);
	lst = lst->next;
	while (lst)
	{
		content = (t_env *)lst->content;
		if (content && content->key
			&& ft_strlen(content->key) == n
			&& ft_strncmp(target, content->key, n) == 0)
		{
			return (content);
		}
		lst = lst->next;
	}
	return (NULL);
}

char	*env_get_value(t_list *env_list, char *target)
{
	t_env	*env;

	env = env_find(env_list, target);
	if (env && env->has_value)
		return (x_strdup(env->value));
	return (NULL);
}

void	env_list_remove(t_list **head, char *key)
{
	t_list	*curr;
	t_list	*prev;
	size_t	len;

	if (!head || !*head || !key)
		return ;
	prev = *head;
	curr = (*head)->next;
	len = ft_strlen(key);
	while (curr)
	{
		if (ft_strncmp(((t_env *)curr->content)->key, key, len + 1) == 0)
		{
			prev->next = curr->next;
			ft_lstdelone(curr, env_free);
			return ;
		}
		prev = curr;
		curr = curr->next;
	}
}
