#include "ft_readline_internal.h"

t_caps	*get_caps(void)
{
	static t_caps	caps;
	static bool		initialized = false;
	char			*term;

	if (initialized)
		return (&caps);
	term = getenv("TERM");
	if (!term)
		term = "xterm";
	if (tgetent(NULL, term) <= 0)
		return (NULL);
	caps.le = tgetstr("le", NULL);
	caps.nd = tgetstr("nd", NULL);
	caps.up = tgetstr("up", NULL);
	caps.dw = tgetstr("do", NULL);
	caps.cl = tgetstr("cl", NULL);
	caps.cr = tgetstr("cr", NULL);
	caps.ce = tgetstr("ce", NULL);
	caps.ks = tgetstr("ks", NULL);
	caps.ke = tgetstr("ke", NULL);
	initialized = true;
	return (&caps);
}
