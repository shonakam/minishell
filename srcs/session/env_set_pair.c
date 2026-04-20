#include "session_internal.h"

bool	env_set_pair(t_list **lst, char *key, char *value)
{
	char	*line;
	bool	res;

	line = join_three(key, "=", value);
	if (!line)
		return (false);
	res = env_set(lst, line);
	free(line);
	return (res);
}
