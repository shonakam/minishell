#include "lexer_internal.h"

t_token_type	get_token_type(const char *str)
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
