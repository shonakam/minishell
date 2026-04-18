#include "lexer_internal.h"

t_token	*handle_operator(char **line, int op_len)
{
	t_token			*token;
	t_token_type	type;
	char			*str;

	str = x_substr(*line, 0, op_len);
	if (!str)
		return (NULL);
	type = get_token_type(str);
	token = token_new(type, QUOTE_NONE, str);
	if (!token)
		return (free(str), NULL);
	*line += op_len;
	return (token);
}
