#include "builtin_internal.h"

static int	update_env_or_add(
	t_context *ctx, char *key, char *value, bool has_value)
{
	t_env	*target;
	t_env	*new_node;

	target = env_find(ctx->env_list, key);
	if (target)
	{
		if (has_value)
		{
			free(target->value);
			if (value)
				target->value = x_strdup(value);
			else
				target->value = x_strdup("");
			target->has_value = true;
		}
		return (EXIT_SUCCESS);
	}
	new_node = env_new(key, value, has_value);
	if (!new_node)
		return (EXIT_FAILURE);
	ft_lstadd_back(&ctx->env_list, ft_lstnew(new_node));
	return (EXIT_SUCCESS);
}

static int	export_single_param(t_context *ctx, char *arg)
{
	char	*sep;
	char	*key;
	char	*value;
	int		status;

	value = NULL;
	sep = ft_strchr(arg, '=');
	if (sep)
	{
		key = ft_substr(arg, 0, sep - arg);
		value = x_strdup(sep + 1);
	}
	else
		key = x_strdup(arg);
	if (!is_valid_identifier(key))
	{
		ft_dprintf(STDERR_FILENO, ERR_INVALID_ID, arg);
		status = EXIT_FAILURE;
	}
	else
		status = update_env_or_add(ctx, key, value, sep != NULL);
	return (status);
}

int	ft_export(t_context *ctx, char **argv)
{
	int	i;
	int	status;

	if (!argv[1])
	{
		print_sorted_export(ctx);
		return (EXIT_SUCCESS);
	}
	i = 1;
	status = EXIT_SUCCESS;
	while (argv[i])
	{
		if (export_single_param(ctx, argv[i]) == EXIT_FAILURE)
			status = EXIT_FAILURE;
		i++;
	}
	return (status);
}
