#include "utils_internal.h"

void	*x_realloc(void *ptr, size_t old_size, size_t new_size)
{
	void	*new_ptr;

	if (new_size == 0)
		return (free(ptr), NULL);
	new_ptr = ft_calloc(1, new_size);
	if (!new_ptr)
		return (free(ptr), ft_dprintf(STDERR_FILENO, ERR_MALLOC), NULL);
	if (ptr)
	{
		ft_memcpy(new_ptr, ptr, old_size);
		free(ptr);
	}
	return (new_ptr);
}
