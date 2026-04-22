#include "../parser_internal.h"

bool	is_pipe_op(t_token_type type)
{
	return (type == TOKEN_PIPE);
}

bool	is_logical_op(t_token_type type)
{
	return (type == TOKEN_AND_IF || type == TOKEN_OR_IF);
}

bool	is_list_op(t_token_type type)
{
	return (type == TOKEN_AMPERSAND || type == TOKEN_SEMICOLON);
}

bool	is_control_op(t_token_type type)
{
	return (is_pipe_op(type) || is_logical_op(type) || is_list_op(type));
}
