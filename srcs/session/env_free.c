#include "session_internal.h"

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
