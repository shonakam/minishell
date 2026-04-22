#include "lexer_internal.h"

void	act_add_char(t_lexer *l, t_token_state *next)
{
	size_t	new_size;

	if (l->buf_idx + 1 >= l->buf_size)
	{
		new_size = l->buf_size * 2;
		l->buffer = x_realloc(l->buffer, l->buf_size, new_size);
		if (!l->buffer)
		{
			l->is_err = true;
			l->is_token_finished = true;
			return ;
		}
		l->buf_size = new_size;
	}
	l->buffer[l->buf_idx++] = l->ch;
	l->buffer[l->buf_idx] = '\0';
	(void)next;
}

void	act_ignore(t_lexer *l, t_token_state *next)
{
	(void)l;
	(void)next;
}

void	act_delimiter(t_lexer *l, t_token_state *next)
{
	l->is_token_finished = true;
	*next = TOKEN_NONE;
}

void	act_end_of_file(t_lexer *l, t_token_state *next)
{
	l->is_token_finished = true;
	*next = TOKEN_NONE;
	(void)l;
}

void	act_add_and_word(t_lexer *l, t_token_state *next)
{
	act_add_char(l, next);
	*next = TOKEN_IN_WORD;
}
