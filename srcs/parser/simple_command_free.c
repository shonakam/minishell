#include "parser_internal.h"

void	simple_command_free(void *content)
{
	t_simple_command	*cmd;

	if (!content)
		return ;
	cmd = (t_simple_command *)content;
	if (cmd->args)
		ft_lstclear(&cmd->args, arg_free);
	if (cmd->redirects)
		ft_lstclear(&cmd->redirects, redirect_free);
	free(cmd);
}
