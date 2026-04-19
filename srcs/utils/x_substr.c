#include "utils_internal.h"

char	*x_substr(char const *s, unsigned int start, size_t len)
{
	char	*res;

	if (!s)
		return (NULL);
	res = ft_substr(s, start, len);
	if (!res)
		ft_dprintf(STDERR_FILENO, ERR_MALLOC);
	return (res);
}
