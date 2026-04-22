#include "lexer_internal.h"

void	lexer_advance(t_lexer *l)
{
	if (l->ch != '\0')
	{
		l->pos++;
		l->ch = l->input[l->pos];
	}
}

char	lexer_peek(t_lexer *l)
{
	if (l->input[l->pos] == '\0')
		return ('\0');
	return (l->input[l->pos + 1]);
}

void	lexer_reset_buffer(t_lexer *l)
{
	l->buf_idx = 0;
	if (l->buffer)
		l->buffer[0] = '\0';
	l->current_type = TOKEN_WORD;
}
