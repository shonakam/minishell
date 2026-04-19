#include "utils_internal.h"

int	x_dup2(int oldfd, int newfd)
{
	int	ret;

	ret = dup2(oldfd, newfd);
	if (ret < 0)
		ft_dprintf(STDERR_FILENO, ERR_DUP2, strerror(errno));
	return (ret);
}
