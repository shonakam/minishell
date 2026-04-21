#include "lexer_internal.h"

static bool	report_quote_error(t_qstate state)
{
	char	quote;

	if (state == QUOTE_SINGLE)
		quote = '\'';
	else
		quote = '"';
	ft_dprintf(STDERR_FILENO, ERR_QUOTE_EOF, quote);
	return (true);
}

bool	is_syntax_valid(t_qstate state)
{
	if (state != QUOTE_NONE)
	{
		report_quote_error(state);
		return (false);
	}
	return (true);
}
