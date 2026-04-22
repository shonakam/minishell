#include "../parser_internal.h"

bool	is_delimiter(t_token_type type)
{
	return (is_control_op(type) || is_eof(type) || is_subshell_end(type));
}

bool	is_command_start(t_token_type type)
{
	return (is_word(type)|| is_subshell_start(type) || is_redirect(type));
}

bool	is_command_element(t_token_type type)
{
	return (is_word(type) || is_io(type) || is_paren(type));
}
