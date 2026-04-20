#include "executor_internal.h"

char	**convert_args_to_argv(t_list *args)
{
	char	**argv;
	int		size;
	int		i;

	size = ft_lstsize(args);
	argv = x_calloc(1, sizeof(char *) * (size + 1));
	i = 0;
	while (args)
	{
		argv[i++] = x_strdup(((t_arg *)args->content)->str);
		args = args->next;
	}
	argv[i] = NULL;
	return (argv);
}
