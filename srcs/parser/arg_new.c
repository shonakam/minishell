#include "parser_internal.h"

t_arg	*arg_new(char *str, t_qstate state)
{
	t_arg	*arg;

	arg = (t_arg *)x_calloc(1, sizeof(t_arg));
	if (!arg)
		return (NULL);
	arg->str = x_strdup(str);
	if (!arg->str)
		return (free(arg), NULL);
	arg->state = state;
	return (arg);
}
