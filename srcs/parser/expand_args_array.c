#include "parser_internal.h"

static size_t	calc_new(size_t current_len)
{
	return (sizeof(char *) * (current_len + 2));
}

static size_t	calc_old(size_t current_len)
{
	if (current_len == 0)
		return (0);
	return (sizeof(char *) * (current_len + 1));
}

char	**expand_args_array(char **args, char *new_arg)
{
	char	**new_args;
	size_t	len;

	len = 0;
	while (args && args[len])
		len++;
	new_args = (char **)x_realloc(args, calc_old(len), calc_new(len));
	if (!new_args)
		return (NULL);
	new_args[len] = ft_strdup(new_arg);
	if (!new_args[len])
		return (NULL);
	new_args[len + 1] = NULL;
	return (new_args);
}