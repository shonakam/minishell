#include "parser_internal.h"

static char	*strip_quotes(const char *src)
{
	size_t	len;

	if (!src)
		return (NULL);
	len = ft_strlen(src);
	if (len < 2)
		return (x_strdup(src));
	return (x_substr(src, 1, len - 2));
}

void	set_heredoc_delimiter(t_redirect *redir, t_token *token)
{
	if (redir->target)
    {
        free(redir->target);
        redir->target = NULL;
    }
	if (token->state != TOKEN_NONE)
	{
		redir->need_expand = false;
		redir->target = strip_quotes(token->str);
	}
	else
	{
		redir->need_expand = true;
		redir->target = x_strdup(token->str);
	}
}
