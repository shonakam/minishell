#include "parser_internal.h"

t_pipeline	*pipeline_new(void)
{
	return ((t_pipeline *)x_calloc(1, sizeof(t_pipeline)));
}
