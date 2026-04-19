#include "utils_internal.h"

int	x_dup(int fd)
{
	int	ret;

	ret = dup(fd);
	if (ret < 0)
		ft_dprintf(STDERR_FILENO, ERR_DUP, strerror(errno));
	return (ret);
}
