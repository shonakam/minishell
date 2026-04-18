#include "parser_internal.h"

t_subshell	*subshell_new(t_ast_node *inner_ast)
{
	t_subshell	*sub;

	sub = (t_subshell *)x_calloc(1, sizeof(t_subshell));
	if (!sub)
		return (NULL);
	sub->inner_ast = inner_ast;
	return (sub);
}
