#include "parser_internal.h"

bool	is_logical_operator(t_token *token)
{
	if (!token)
		return (false);
	return (token->type == TOKEN_AND_IF || token->type == TOKEN_OR_IF);
}

bool	is_list_operator(t_token *token)
{
	if (!token)
		return (false);
	return (token->type == TOKEN_SEMICOLON
		|| token->type == TOKEN_AMPERSAND
		|| token->type == TOKEN_NEWLINE);
}

bool	is_token_redirect(t_token *token)
{
	if (!token)
		return (false);
	return (token->type == TOKEN_REDIRECT_IN
		|| token->type == TOKEN_REDIRECT_OUT
		|| token->type == TOKEN_APPEND
		|| token->type == TOKEN_HEREDOC);
}

bool	is_token_word(t_token *token)
{
	if (!token)
		return (false);
	return (token->type == TOKEN_WORD);
}

bool	is_command_element(t_token *token)
{
	return (is_token_word(token) || is_token_redirect(token));
}
