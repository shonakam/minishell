#include "lexer_internal.h"

t_token	*token_new(t_token_type type, t_qstate state, char *str)
{
	t_token	*new;

	new = (t_token *)x_calloc(1, sizeof(t_token));
	if (!new)
		return (NULL);
	new->type = type;
	new->state = state;
	new->str = str;
	return (new);
}
