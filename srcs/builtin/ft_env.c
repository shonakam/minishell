#include "builtin_internal.h"

/*
 * ft_env:
 * Prints the current environment variables.
 * * Note: In this minishell, 'env' is implemented as a simple builtin
 * that does not support executing other commands with arguments.
 * It strictly displays environment variables that have an assigned value.
 *
 * According to Bash, only environment variables with a value
 * (e.g., KEY=VALUE) are displayed by 'env'.
 * Variables that were exported without an assignment (e.g., 'export KEY')
 * are kept in the list but ignored here.
 */
int	ft_env(t_context *ctx, char **argv)
{
	t_list	*node;
	t_env	*env;

	if (argv[1])
	{
		ft_dprintf(STDERR_FILENO, ERR_TOO_MANY_ARGS, "env");
		return (EXIT_FAILURE);
	}
	node = ctx->env_list->next;
	while (node)
	{
		env = (t_env *)node->content;
		if (env->has_value)
			ft_printf("%s=%s\n", env->key, env->value);
		node = node->next;
	}
	return (EXIT_SUCCESS);
}
