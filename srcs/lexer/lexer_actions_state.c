#include "lexer_internal.h"

void	act_quote_open(t_lexer *l, t_token_state *next)
{
	if (l->ch == '\'')
	{
		*next = TOKEN_IN_SINGLE;
		l->quote_state = TOKEN_IN_SINGLE;
	}
	else if (l->ch == '\"')
	{
		*next = TOKEN_IN_DOUBLE;
		if (l->quote_state != TOKEN_IN_SINGLE)
            l->quote_state = TOKEN_IN_DOUBLE;
	}
}

void	act_quote_close(t_lexer *l, t_token_state *next)
{
	*next = TOKEN_IN_WORD;
	(void)l;
}
