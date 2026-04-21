#include "session_internal.h"

t_env	*env_parse_line(char *line)
{
	char	*sep;
	char	*kv[2];
	bool	has_val;

	sep = ft_strchr(line, '=');
	if (sep)
	{
		kv[0] = x_substr(line, 0, sep - line);
		kv[1] = x_strdup(sep + 1);
		has_val = true;
	}
	else
	{
		kv[0] = x_strdup(line);
		kv[1] = NULL;
		has_val = false;
	}
	if (!kv[0] || (has_val && !kv[1]))
		return (free(kv[0]), free(kv[1]), NULL);
	return (env_new(kv[0], kv[1], has_val));
}
