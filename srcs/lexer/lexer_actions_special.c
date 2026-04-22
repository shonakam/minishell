#include "lexer_internal.h"

void	act_handle_meta(t_lexer *l, t_token_state *next)
{
	char			tmp[3];
	t_token_type	type;

	tmp[0] = l->ch;
	tmp[1] = lexer_peek(l);
	tmp[2] = '\0';
	type = token_get_type(tmp);
	if (type == TOKEN_WORD)
	{
		tmp[1] = '\0';
		type = token_get_type(tmp);
	}
	l->current_type = type;
	act_add_char(l, next);
	if (type == TOKEN_AND_IF || type == TOKEN_OR_IF
		|| type == TOKEN_APPEND || type == TOKEN_HEREDOC)
	{
		lexer_advance(l);
		act_add_char(l, next);
	}
	lexer_advance(l);
	l->is_token_finished = true;
	*next = TOKEN_NONE;
}

void	act_err_unclosed(t_lexer *l, t_token_state *next)
{
	char    *missing_char;

	if (*next == TOKEN_IN_SINGLE)
		missing_char = "'";
	else if (*next == TOKEN_IN_DOUBLE)
		missing_char = "\"";
	else
		missing_char = "EOF";
	ft_dprintf(STDERR_FILENO, ERR_SYNTAX_TOKEN, missing_char);
	l->is_err = true;
	l->is_token_finished = true;
	*next = TOKEN_NONE;
}

void	act_handle_dollar(t_lexer *l, t_token_state *next)
{
	act_add_char(l, next);
	if (lexer_peek(l) == '?')
	{
		lexer_advance(l);
		act_add_char(l, next);
		lexer_advance(l);
		l->is_token_finished = true;
	}
}
