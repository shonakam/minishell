#include "../parser_internal.h"

t_redirect	*redirect_new(t_redir_type type, char *target)
{
	t_redirect	*redir;

	redir = (t_redirect *)x_calloc(1, sizeof(t_redirect));
	if (!redir)
		return (NULL);
	redir->type = type;
	redir->target = x_strdup(target);
	if (!redir->target)
		return (free(redir), NULL);
	redir->fd = -1;
	return (redir);
}

void	redirect_free(void *content)
{
	t_redirect	*redir;

	if (!content)
		return ;
	redir = (t_redirect *)content;
	if (redir->tmp_filename)
	{
		unlink(redir->tmp_filename);
		free(redir->tmp_filename);
	}
	free(redir->target);
	free(redir);
}

bool	redirect_is_empty(t_redirect *redir)
{
	if (!redir)
		return (true);
	if (!redir->target || !redir->target[0])
		return (true);
	return (false);
}
