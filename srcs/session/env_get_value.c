#include "session_internal.h"

char	*env_get_value(t_list *env_list, char *target)
{
	t_env	*env;

	env = env_find(env_list, target);
	if (env && env->has_value)
		return (x_strdup(env->value));
	return (NULL);
}
