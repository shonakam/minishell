#include "parser_internal.h"

void	pipeline_free(t_pipeline *pipeline)
{
	if (!pipeline)
		return ;
	ft_lstclear(&pipeline->simple_commands, simple_command_free);
	free(pipeline);
}
