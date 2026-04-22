#include "../parser_internal.h"

bool	is_next_token_valid(t_context *ctx, t_list **tokens, t_token_rule is_ok)
{
	t_token	*next;
	char	*err_str;

	next = token_peek(tokens);
	if (!next || !is_ok(next->type))
	{
		if (!next || next->type == TOKEN_NEWLINE)
			err_str = "newline";
		else
			err_str = next->str;
		parser_syntax_error(ctx, err_str);
		return (false);
	}
	return (true);
}
