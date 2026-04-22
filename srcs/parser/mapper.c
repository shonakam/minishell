#include "parser_internal.h"

t_node_type	get_node_type(t_token_type type)
{
	if (type == TOKEN_AND_IF)
		return (NODE_AND);
	if (type == TOKEN_OR_IF)
		return (NODE_OR);
	if (type == TOKEN_PIPE)
		return (NODE_PIPELINE);
	if (type == TOKEN_AMPERSAND)
		return (NODE_BACKGROUND);
	if (type == TOKEN_LPAREN)
		return (NODE_SUBSHELL);
	return (NODE_COMMAND);
}

t_redir_type	get_redir_type(t_token_type type)
{
	if (type == TOKEN_REDIRECT_IN)
		return (REDIR_IN);
	if (type == TOKEN_REDIRECT_OUT)
		return (REDIR_OUT);
	if (type == TOKEN_APPEND)
		return (REDIR_APPEND);
	return (REDIR_HEREDOC);
}

t_node_type	get_current_node_type(t_list *tokens)
{
	t_token	*t;

	if (!tokens || !tokens->content)
		return (NODE_COMMAND);
	t = (t_token *)tokens->content;
	return (get_node_type(t->type));
}

t_redir_type	get_current_redir_type(t_list *tokens)
{
	t_token	*t;

	if (!tokens || !tokens->content)
		return (REDIR_OUT);
	t = (t_token *)tokens->content;
	return (get_redir_type(t->type));
}
