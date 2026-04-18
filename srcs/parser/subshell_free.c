#include "parser_internal.h"

void	subshell_free(t_subshell *sub)
{
	if (!sub)
		return ;
	ast_node_free(sub->inner_ast);
	ft_lstclear(&sub->redirects, redirect_free);
	free(sub);
}
