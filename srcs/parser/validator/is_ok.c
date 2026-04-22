#include "../parser_internal.h"

bool	is_ok_background(t_token_type type)
{
	if (is_command_start(type))
		return (true);
	return (type == TOKEN_NEWLINE
			|| type == TOKEN_EOF
			|| type == TOKEN_RPAREN);
}

bool	is_ok_list(t_token_type type)
{
	if (type == TOKEN_WORD
		|| type == TOKEN_LPAREN
		|| type == TOKEN_REDIRECT_IN
		|| type == TOKEN_REDIRECT_OUT
		|| type == TOKEN_APPEND
		|| type == TOKEN_HEREDOC)
		return (true);
	if (type == TOKEN_NEWLINE || type == TOKEN_EOF)
		return (true);
	return (false);
}

bool	is_ok_pipeline(t_token_type type)
{
	return (type == TOKEN_WORD
		|| type == TOKEN_LPAREN
		|| type == TOKEN_REDIRECT_IN
		|| type == TOKEN_REDIRECT_OUT
		|| type == TOKEN_APPEND
		|| type == TOKEN_HEREDOC);
}

bool	is_ok_command(t_token_type type)
{
	return (type == TOKEN_WORD
		|| type == TOKEN_REDIRECT_IN
		|| type == TOKEN_REDIRECT_OUT
		|| type == TOKEN_APPEND
		|| type == TOKEN_HEREDOC);
}
