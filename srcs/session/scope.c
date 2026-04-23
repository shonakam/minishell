#include "session_internal.h"

void	scope_init(t_scope *scope)
{
	if (!scope)
		return ;
	ft_memset(scope, 0, sizeof(t_scope));
}

void	scope_clear(t_scope *scope)
{
	if (!scope)
		return ;
	if (scope->line)
		free(scope->line);
	if (scope->tokens)
		ft_lstclear(&scope->tokens_anchor, token_free);
	if (scope->ast)
		ast_node_free(scope->ast);
	if (scope->job)
		job_free(scope->job);
	scope_init(scope);
}
