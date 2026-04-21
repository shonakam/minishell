#include "ft_readline_internal.h"

static struct termios	*get_term_storage(void)
{
	static struct termios	saved;

	return (&saved);
}

bool	termios_change_to_raw(void)
{
	struct termios	raw;

	raw = *get_term_storage();
	raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
	raw.c_oflag &= ~(OPOST);
	raw.c_lflag &= ~(ICANON | ECHO | IEXTEN | ECHOCTL);
	raw.c_cc[VMIN] = 1;
	raw.c_cc[VTIME] = 0;
	return (tcsetattr(STDIN_FILENO, TCSANOW, &raw) == 0);
}

bool	termios_change_to_shell_default(void)
{
	struct termios	std;

	std = *get_term_storage();
	std.c_lflag &= ~ECHOCTL;
	return (tcsetattr(STDIN_FILENO, TCSANOW, &std) == 0);
}

bool	termios_ctl(bool is_init)
{
	static struct termios	original;
	static bool				is_saved = false;

	if (is_init)
	{
		if (is_saved)
			return (true);
		if (tcgetattr(STDIN_FILENO, &original) == -1)
			return (false);
		is_saved = true;
		return (true);
	}
	else
	{
		if (!is_saved)
			return (false);
		return (tcsetattr(STDIN_FILENO, TCSAFLUSH, &original) == 0);
	}
}
