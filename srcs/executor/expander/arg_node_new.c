#include "../executor_internal.h"

t_list	*arg_node_new(char *content)
{
	t_arg	*arg;
	t_list	*node;

	arg = x_calloc(1, sizeof(t_arg));
	arg->str = x_strdup(content);
	if (!arg->str)
		return (NULL);
	arg->state = QUOTE_NONE;
	node = x_lstnew(arg);
	if (!node)
		return (arg_free(arg), NULL);
	return (node);
}
