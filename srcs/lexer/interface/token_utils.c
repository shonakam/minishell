#include "../lexer_internal.h"

t_token	*token_consume(t_list **tokens)
{
	t_token	*token;

	if (!tokens || !*tokens)
		return (NULL);
	token = (t_token *)(*tokens)->content;
	*tokens = (*tokens)->next;
	return (token);
}

t_token	*token_peek(t_list **tokens)
{
	if (!tokens || !*tokens)
		return (NULL);
	return ((t_token *)((*tokens)->content));
}

t_token_type	token_peek_type(t_list **tokens)
{
	t_token	*token;

	if (!tokens)
		return (TOKEN_EOF);
	token = (t_token *)((*tokens)->content);
	if (!token)
		return (TOKEN_EOF);
	return (token->type);
}

t_token_type	token_get_type(const char *str)
{
	if (ft_strncmp(str, OP_AND_IF, 2) == 0)
		return (TOKEN_AND_IF);
	if (ft_strncmp(str, OP_OR_IF, 2) == 0)
		return (TOKEN_OR_IF);
	if (ft_strncmp(str, OP_APPEND, 2) == 0)
		return (TOKEN_APPEND);
	if (ft_strncmp(str, OP_HEREDOC, 2) == 0)
		return (TOKEN_HEREDOC);
	if (ft_strncmp(str, "|", 1) == 0)
		return (TOKEN_PIPE);
	if (ft_strncmp(str, "<", 1) == 0)
		return (TOKEN_REDIRECT_IN);
	if (ft_strncmp(str, ">", 1) == 0)
		return (TOKEN_REDIRECT_OUT);
	if (ft_strncmp(str, ";", 1) == 0)
		return (TOKEN_SEMICOLON);
	if (ft_strncmp(str, "\n", 1) == 0)
		return (TOKEN_NEWLINE);
	if (ft_strncmp(str, "&", 1) == 0)
		return (TOKEN_AMPERSAND);
	if (ft_strncmp(str, "(", 1) == 0)
		return (TOKEN_LPAREN);
	if (ft_strncmp(str, ")", 1) == 0)
		return (TOKEN_RPAREN);
	return (TOKEN_WORD);
}
