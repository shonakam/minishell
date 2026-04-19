#include "utils_internal.h"

t_list	*x_lstnew(void *content)
{
	t_list	*new;

	new = ft_lstnew(content);
	if (!new)
		ft_dprintf(STDERR_FILENO, ERR_MALLOC);
	return (new);
}
