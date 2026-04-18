#include "parser_internal.h"

t_redirect	*redirect_new(t_redir_type type, char *target)
{
	t_redirect	*redir;

	redir = (t_redirect	*)x_calloc(1, sizeof(t_redirect));
	if (!redir)
		return (NULL);
	redir->type = type;
	redir->target = target;
	redir->fd = -1;
	return (redir);
}
