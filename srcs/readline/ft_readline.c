#include "ft_readline_internal.h"

static bool	handle_readline_signal(t_readline_state *s)
{
	if (g_signal_flag == SIGINT)
	{
		g_signal_flag = 0;
		free(s->buf);
		s->buf = NULL;
		termios_change_to_shell_default();
		return (true);
	}
	return (false);
}

/* If errno == EINTR, we loop and try again */
static bool	read_next_char(t_readline_state *s)
{
	while (true)
	{
		s->read = read(STDIN_FILENO, s->in, RL_BUFF_SIZE - 1);
		if (s->read > 0)
		{
			s->in[s->read] = '\0';
			return (true);
		}
		if (s->read == 0)
			return (false);
		if (errno != EINTR)
			return (false);
	}
}

char	*ft_readline(const char *prompt)
{
	t_readline_state	s;

	init_readline_state(&s, prompt);
	termios_change_to_raw();
	write(STDOUT_FILENO, prompt, ft_strlen(prompt));
	while (true)
	{
		if (handle_readline_signal(&s))
			return (NULL);
		if (!read_next_char(&s))
			break ;
		if (!controller(&s))
			break ;
	}
	termios_change_to_shell_default();
	debug_print_green_line();
	debug_print_memory(s.buf, s.size / 16);
	debug_print_green_line();
	destroy_readline_state(&s);
	return (s.buf);
}
