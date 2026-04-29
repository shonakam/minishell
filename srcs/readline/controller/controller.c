#include "../ft_readline_internal.h"

static bool	expand_buffer(t_readline_state *s)
{
	char	*new_buf;
	size_t	new_size;

	new_size = s->size * 2;
	new_buf = x_realloc(s->buf, s->size, new_size);
	if (!new_buf)
		return (false);
	s->buf = new_buf;
	s->size = new_size;
	return (true);
}

/*
** [action_insert flow]
** 1. Check buffer capacity: Ensure there is space for the
**    new char + null terminator.
** 2. Shift memory: Move existing characters (including \0)
**    from index one slot to the right.
** 3. Insert character: Place the new character
**    into the gap created at the current index.
** 4. Redraw screen: Write the inserted character
**    and the shifted suffix to the terminal.
** 5. Restore cursor:
**      Move the cursor back to the right of the newly inserted character.
*/
static bool	action_insert(t_readline_state *s)
{
	size_t	cur_len;
	size_t	suffix_len;
	size_t	i;

	cur_len = ft_strlen(s->buf + s->index);
	if (cur_len + 2 >= s->size)
		if (!expand_buffer(s))
			return (false);
	suffix_len = ft_strlen(s->buf + s->index);
	ft_memmove(s->buf + s->index + 1, s->buf + s->index, suffix_len + 1);
	s->buf[s->index] = (char)s->current_c;
	write(STDOUT_FILENO, s->buf + s->index, suffix_len + 1);
	i = 0;
	while (i++ < suffix_len)
		tputs(s->caps->le, 1, putchar_int);
	s->index++;
	return (true);
}

bool	controller(t_readline_state *s)
{
	ssize_t	i;

	i = 0;
	while (i < s->read)
	{
		s->current_c = (unsigned char)s->in[i];
		if (s->in[0] == K_ESC && s->read > 1)
		{
			i += handle_cursor(s, i);
			continue ;
		}
		if (!handle_eot(s))
			return (false);
		if (!handle_newline(s))
			return (false);
		handle_backspace(s);
		if (ft_isprint(s->current_c))
		{
			if (!action_insert(s))
				return (false);
		}
		i++;
	}
	return (true);
}
