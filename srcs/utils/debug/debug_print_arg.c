#include "../utils_internal.h"

void	debug_print_arg(void *content)
{
	t_arg	*arg;

	if (!content)
	{
		printf("[Arg] (null)\r\n");
		return ;
	}
	arg = (t_arg *)content;
	printf("[Arg] str: [%s], state: [%d]\r\n",
		arg->str ? arg->str : "(null)",
		arg->state);
}
