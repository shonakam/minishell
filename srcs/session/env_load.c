#include "session_internal.h"

t_list	*env_load(char **envp)
{
	t_list	*env_list;

	if (!envp)
		return (NULL);
	env_list = x_lstnew(NULL);
	if (!env_list)
		return (NULL);
	while (*envp)
	{
		if (!env_set(&env_list, *envp))
		{
			ft_lstclear(&env_list, env_free);
			return (NULL);
		}
		envp++;
	}
	return (env_list);
}
