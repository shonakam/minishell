#include "../parser_internal.h"

t_simple_command	*simple_command_new(void)
{
	return (x_calloc(1, sizeof(t_simple_command)));
}

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

bool	simple_command_is_empty(t_simple_command *cmd)
{
	if (!cmd)
		return (true);
	return (cmd->args == NULL && cmd->redirects == NULL);
}
