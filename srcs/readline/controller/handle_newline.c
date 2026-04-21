#include "../ft_readline_internal.h"

bool	handle_newline(t_readline_state *s)
{
	if (s->current_c == K_CR || s->current_c == K_LF)
	{
		ft_putstr_fd(CRLF, STDOUT_FILENO);
		return (false);
	}
	return (true);
}
