#include "../parser_internal.h"

bool	is_word(t_token_type type)
{
	return (type == TOKEN_WORD);
}

bool	is_subshell_start(t_token_type type)
{
	return (type == TOKEN_LPAREN);
}

bool	is_subshell_end(t_token_type type)
{
	return (type == TOKEN_RPAREN);
}

bool	is_io(t_token_type type)
{
	return (type == TOKEN_REDIRECT_IN || type == TOKEN_REDIRECT_OUT
		|| type == TOKEN_APPEND || type == TOKEN_HEREDOC);
}

bool	is_eof(t_token_type type)
{
	return (type == TOKEN_EOF || type == TOKEN_NEWLINE);
}
