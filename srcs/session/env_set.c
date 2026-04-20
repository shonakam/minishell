#include "session_internal.h"

static void	update_existing_env(t_env *existing, t_env *new_data)
{
	free(existing->value);
	existing->value = new_data->value;
	existing->has_value = new_data->has_value;
	free(new_data->key);
	free(new_data);
}

static bool	append_new_env(t_list **lst, t_env *new_data)
{
	t_list	*new_node;

	new_node = x_lstnew((void *)new_data);
	if (!new_node)
	{
		env_free(new_data);
		return (false);
	}
	ft_lstadd_back(lst, new_node);
	return (true);
}

bool	env_set(t_list **lst, char *line)
{
	t_env	*new_data;
	t_env	*existing;

	if (!lst || !line)
		return (false);
	new_data = env_parse_line(line);
	if (!new_data)
		return (false);
	existing = env_find(*lst, new_data->key);
	if (existing)
	{
		update_existing_env(existing, new_data);
		return (true);
	}
	return (append_new_env(lst, new_data));
}
