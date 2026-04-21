#include "parser_internal.h"

void	redirect_free(void *content)
{
	t_redirect	*redir;

	if (!content)
		return ;
	redir = (t_redirect *)content;
	if (redir->tmp_filename)
		free(redir->tmp_filename);
	free(redir->target);
	free(redir);
}
