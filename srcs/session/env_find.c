#include "session_internal.h"

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
