#include "../session_internal.h"

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

t_env	*env_parse_line(char *line)
{
	char	*sep;
	char	*kv[2];
	bool	has_val;

	sep = ft_strchr(line, '=');
	if (sep)
	{
		kv[0] = x_substr(line, 0, sep - line);
		kv[1] = x_strdup(sep + 1);
		has_val = true;
	}
	else
	{
		kv[0] = x_strdup(line);
		kv[1] = NULL;
		has_val = false;
	}
	if (!kv[0] || (has_val && !kv[1]))
		return (free(kv[0]), free(kv[1]), NULL);
	return (env_new(kv[0], kv[1], has_val));
}

bool	env_set_pair(t_list **lst, char *key, char *value)
{
	char	*line;
	bool	res;

	line = join_three(key, "=", value);
	if (!line)
		return (false);
	res = env_set(lst, line);
	free(line);
	return (res);
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
