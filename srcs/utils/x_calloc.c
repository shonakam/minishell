#include "utils_internal.h"

void	*x_calloc(size_t count, size_t size)
{
	void	*ptr;

	ptr = ft_calloc(count, size);
	if (!ptr)
		ft_dprintf(STDERR_FILENO, ERR_MALLOC);
	return (ptr);
}
