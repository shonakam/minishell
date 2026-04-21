#include "ft_readline_internal.h"

void	init_readline_state(t_readline_state *s, const char *prompt)
{
	ft_memset(s, 0, sizeof(t_readline_state));
	s->prompt = (char *)prompt;
	s->buf = x_calloc(BUFFER_SIZE, sizeof(char));
	s->size = BUFFER_SIZE;
	s->caps = get_caps();
}

void	destroy_readline_state(t_readline_state *s)
{
	if (!s)
		return ;
	if (s->save_buf)
	{
		free(s->save_buf);
		s->save_buf = NULL;
	}
	s->index = 0;
	s->size = 0;
	s->read = 0;
}
