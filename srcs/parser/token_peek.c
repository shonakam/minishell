#include "parser_internal.h"

t_token	*token_peek(t_list **tokens)
{
	if (!tokens || !*tokens)
		return (NULL);
	return ((t_token *)((*tokens)->content));
}

t_token_type	token_peek_type(t_list **tokens)
{
	t_token	*token;

	if (!tokens)
		return (TOKEN_EOF);
	token = (t_token *)((*tokens)->content);
	if (!token)
		return (TOKEN_EOF);
	return (token->type);
}
