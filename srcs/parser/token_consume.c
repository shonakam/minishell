#include "parser_internal.h"

t_token	*token_consume(t_list **tokens)
{
	t_token	*token;

	if (!tokens || !*tokens)
		return (NULL);
	token = (t_token *)(*tokens)->content;
	*tokens = (*tokens)->next;
	return (token);
}
