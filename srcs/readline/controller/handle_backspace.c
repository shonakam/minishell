#include "../ft_readline_internal.h"

void	handle_backspace(t_readline_state *s)
{
	size_t	suffix_len;
	size_t	i;

	if (s->current_c == K_BS || s->current_c == K_BACKSPACE)
	{
		if (s->index > 0)
		{
			s->index--;
			suffix_len = ft_strlen(s->buf + s->index + 1);
			ft_memmove(
				s->buf + s->index, s->buf + s->index + 1, suffix_len + 1);
			tputs(s->caps->le, 1, putchar_int);
			write(STDOUT_FILENO, s->buf + s->index, suffix_len);
			write(STDOUT_FILENO, " ", 1);
			i = 0;
			while (i++ <= suffix_len)
				tputs(s->caps->le, 1, putchar_int);
		}
	}
}
