#include "utils_internal.h"

char	*x_strdup(const char *s)
{
	char	*res;

	res = ft_strdup(s);
	if (!res)
		ft_dprintf(STDERR_FILENO, ERR_MALLOC);
	return (res);
}
