#include "parser_internal.h"

bool is_ok_command(t_token_type type)
{
	return (type == TOKEN_WORD ||
            type == TOKEN_REDIRECT_IN ||
            type == TOKEN_REDIRECT_OUT ||
            type == TOKEN_APPEND ||
            type == TOKEN_HEREDOC);
}

bool is_ok_pipeline(t_token_type type)
{
	return (type == TOKEN_WORD ||
			type == TOKEN_LPAREN ||
			type == TOKEN_REDIRECT_IN ||
			type == TOKEN_REDIRECT_OUT ||
			type == TOKEN_APPEND ||
			type == TOKEN_HEREDOC);
}

bool is_ok_list(t_token_type type)
{
	if (type == TOKEN_WORD || type == TOKEN_LPAREN ||
			type == TOKEN_REDIRECT_IN ||
			type == TOKEN_REDIRECT_OUT ||
			type == TOKEN_APPEND ||
			type == TOKEN_HEREDOC)
		return (true);
	if (type == TOKEN_NEWLINE || type == TOKEN_EOF)
		return (true);
	return (false);
}

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
