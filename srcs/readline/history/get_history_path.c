#include "../ft_readline_internal.h"

char	*get_history_path(void)
{
	char	*home;
	char	*path;

	home = getenv("HOME");
	if (!home)
		return (NULL);
	path = join_three(home, "/", HIST_FILE_NAME);
	return (path);
}
