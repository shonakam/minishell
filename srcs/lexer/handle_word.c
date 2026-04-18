#include "lexer_internal.h"

static bool	is_word_boundary(char c, t_qstate state)
{
	if (state != QUOTE_NONE)
		return (false);
	if (ft_is_whitespace(c) || ft_strchr(OPERATOR_CHARS, c))
		return (true);
	return (false);
}

t_token	*handle_word(char **line, t_qstate *state)
{
	char		*start;
	char		*word_str;
	int			len;
	t_qstate	attr;

	start = *line;
	len = 0;
	fsm(state, (*line)[len++]);
	attr = *state;
	while ((*line)[len] && !is_word_boundary((*line)[len], *state))
		fsm(state, (*line)[len++]);
	word_str = x_substr(start, 0, len);
	if (!word_str)
		return (NULL);
	*line += len;
	return (token_new(TOKEN_WORD, attr, word_str));
}
