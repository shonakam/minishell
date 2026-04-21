#include "parser_internal.h"

void	arg_free(void *content)
{
	t_arg	*arg;

	if (!content)
		return ;
	arg = (t_arg *)content;
	if (arg->str)
		free(arg->str);
	free(arg);
}
