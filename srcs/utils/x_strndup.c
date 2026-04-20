#include "utils_internal.h"

char	*x_strndup(const char *s, size_t n)
{
	char	*dup;
	size_t	len;

	len = 0;
	while (s[len] && len < n)
		len++;
	dup = (char *)x_calloc(1, len + 1);
	ft_memcpy(dup, s, len);
	dup[len] = '\0';
	return (dup);
}
