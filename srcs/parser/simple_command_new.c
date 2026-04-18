#include "parser_internal.h"

t_simple_command	*simple_command_new(void)
{
	return (x_calloc(1, sizeof(t_simple_command)));
}
