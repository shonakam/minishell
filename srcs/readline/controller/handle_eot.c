#include "../ft_readline_internal.h"

bool	handle_eot(t_readline_state *s)
{
	if (s->current_c == K_CTRL_D)
	{
		if (s->index == 0)
		{
			ft_putstr_fd(CRLF "exit" CRLF, STDOUT_FILENO);
			free(s->buf);
			s->buf = NULL;
			return (false);
		}
		return (true);
	}
	return (true);
}
