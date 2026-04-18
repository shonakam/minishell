#include "parser_internal.h"

void	simple_command_free(void *content)
{
	t_simple_command	*cmd;
	size_t				i;

	if (!content)
		return ;
	cmd = (t_simple_command *)content;
	if (cmd->args)
	{
		i = 0;
		while (cmd->args[i])
			free(cmd->args[i++]);
		free(cmd->args);
	}
	ft_lstclear(&cmd->redirects, redirect_free);
	free (cmd);
}
