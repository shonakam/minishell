#include "utils_internal.h"

int	x_open(char *path, int flags, mode_t mode)
{
	int	fd;

	if (!path)
		return (-1);
	if (flags & O_CREAT)
		fd = open(path, flags, mode);
	else
		fd = open(path, flags);
	if (fd == -1)
	{
		ft_dprintf(STDERR_FILENO, ERR_OPEN, path, strerror(errno));
	}
	return (fd);
}
