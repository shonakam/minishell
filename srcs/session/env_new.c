#include "session_internal.h"

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
