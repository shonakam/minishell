#include "utils_internal.h"

bool	x_fork(pid_t *pid)
{
	*pid = fork();
	if (*pid < 0)
	{
		ft_dprintf(STDERR_FILENO, ERR_FORK, strerror(errno));
		return (false);
	}
	return (true);
}
