#include "parser_internal.h"

void		redirect_free(void *content)
{
	t_redirect	*redir;

	if (!content)
		return ;
	redir = (t_redirect *)content;
	free(redir->target);
	free(redir);
}
