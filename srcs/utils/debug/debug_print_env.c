#include "../utils_internal.h"

void	debug_print_env(void *content)
{
	t_env	*env;

	if (!content)
		return ;
	env = (t_env *)content;
	printf("Env: [%s]=[%s] (has_value: %s)\n",
		env->key,
		env->value ? env->value : "(null)",
		env->has_value ? "true" : "false");
}
