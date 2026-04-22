#include "../lexer_internal.h"

t_token	*token_new(t_lexer *l)
{
	t_token	*tok;

	if (l->buf_idx == 0 && !l->is_err)
		return (NULL);
	tok = x_calloc(1, sizeof(t_token));
	if (!tok)
		return (NULL);
	tok->str = x_strdup(l->buffer);
	tok->type = l->current_type;
	return (tok);
}

t_token	*token_create(t_token_type type, const char *str)
{
	t_token	*tok;

	tok = x_calloc(1, sizeof(t_token));
	if (!tok)
		return (NULL);
	tok->str = x_strdup(str);
	if (!tok->str)
		return (free(tok), NULL);
	tok->type = type;
	return (tok);
}

void	token_free(void *content)
{
	t_token	*token;

	if (!content)
		return ;
	token = (t_token *)content;
	if (token->str)
	{
		free(token->str);
		token->str = NULL;
	}
	free(token);
}

bool	token_append(t_list **list, t_token *t)
{
	t_list	*node;

	if (!t)
		return (false);
	node = x_lstnew(t);
	if (!node)
		return (token_free(t), false);
	ft_lstadd_back(list, node);
	return (true);
}
