#include "../parser_internal.h"

t_subshell	*subshell_new(t_ast_node *inner_ast)
{
	t_subshell	*sub;

	sub = (t_subshell *)x_calloc(1, sizeof(t_subshell));
	if (!sub)
		return (NULL);
	sub->inner_ast = inner_ast;
	return (sub);
}

void	subshell_free(t_subshell *sub)
{
	if (!sub)
		return ;
	ast_node_free(sub->inner_ast);
	ft_lstclear(&sub->redirects, redirect_free);
	free(sub);
}

bool	subshell_is_empty(t_subshell *sub)
{
	if (!sub)
		return (true);
	if (!ast_node_is_empty(sub->inner_ast))
		return (false);
	if (sub->redirects != NULL)
		return (false);
	return (true);
}
