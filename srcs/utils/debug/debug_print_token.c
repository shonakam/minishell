#include "../utils_internal.h"

void	debug_print_token(void *content)
{
	t_token	*token;
	const char  *s;

	if (!content)
		return ;
	token = (t_token *)content;

	static const char *names[] = {
		[TOKEN_WORD] = "WORD",
		[TOKEN_SEMICOLON] = "SEMICOLON",
		[TOKEN_PIPE] = "PIPE",
		[TOKEN_REDIRECT_IN] = "RED_IN",
		[TOKEN_REDIRECT_OUT] = "RED_OUT",
		[TOKEN_APPEND] = "APPEND",
		[TOKEN_HEREDOC] = "HEREDOC",
		[TOKEN_AND_IF] = "AND_IF",
		[TOKEN_OR_IF] = "OR_IF",
		[TOKEN_AMPERSAND] = "AMP",
		[TOKEN_LPAREN] = "LPAREN",
		[TOKEN_RPAREN] = "RPAREN",
		[TOKEN_NEWLINE] = "NEWLINE",
		[TOKEN_EOF] = "EOF"
	};

	printf("Token: [%-10s] | State: %d | Str: [", names[token->type], token->state);
	s = token->str;
	while (s && *s)
	{
		if (*s == '\n')
			printf("\\n");
		else if (*s == '\t')
			printf("\\t");
		else
			putchar(*s);
		s++;
	}
	printf("]\r\n");
}
