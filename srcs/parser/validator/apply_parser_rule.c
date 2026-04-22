#include "../parser_internal.h"

bool	apply_parser_rule(t_token_rule rule, t_list *tokens)
{
	t_token	*token;

	if (!tokens || !tokens->content)
		return (rule(TOKEN_EOF));
	token = (t_token *)tokens->content;
	return (rule(token->type));
}
