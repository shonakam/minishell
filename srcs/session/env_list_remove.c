#include "session_internal.h"

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
