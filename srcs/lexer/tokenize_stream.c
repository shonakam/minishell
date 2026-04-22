#include "lexer_internal.h"

static t_char_event	get_char_event(char c)
{
	if (c == '\0')
		return (EV_EOF);
	if (ft_is_whitespace(c))
		return (EV_SPACE);
	if (c == '\'')
		return (EV_SQUOTE);
	if (c == '\"')
		return (EV_DQUOTE);
	if (c != '\0' && ft_strchr(OPERATOR_CHARS, c) != NULL)
		return (EV_META);
	if (c == '$')
		return (EV_DOLLAR);
	return (EV_CHAR);
}

t_token	*tokenize_stream(t_lexer *l)
{
	t_token_state	current_state;
	t_char_event	event;

	if (l->ch == '\0' && l->pos > 0)
		return (NULL);
	lexer_reset_buffer(l);
	current_state = TOKEN_NONE;
	l->is_token_finished = false;
	while (!l->is_token_finished)
	{
		event = get_char_event(l->ch);
		if ((*l->table)[current_state][event])
			(*l->table)[current_state][event](l, &current_state);
		if (event == EV_EOF || l->is_token_finished)
		{
			l->is_token_finished = true;
			break ;
		}
		if (!l->is_token_finished)
			lexer_advance(l);
	}
	return (token_new(l));
}
