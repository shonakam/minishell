#include "../parser_internal.h"

t_pipeline	*pipeline_new(void)
{
	return ((t_pipeline *)x_calloc(1, sizeof(t_pipeline)));
}

void	pipeline_free(t_pipeline *pipeline)
{
	if (!pipeline)
		return ;
	ft_lstclear(&pipeline->simple_commands, simple_command_free);
	free(pipeline);
}

bool	pipeline_is_empty(t_pipeline *pipeline)
{
	t_list	*curr;

	if (!pipeline || !pipeline->simple_commands)
		return (true);
	curr = pipeline->simple_commands;
	while (curr)
	{
		if (!simple_command_is_empty((t_simple_command *)curr->content))
			return (false);
		curr = curr->next;
	}
	return (true);
}
