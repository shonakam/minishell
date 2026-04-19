#include "utils_internal.h"

bool	x_pipe(int pipefd[2])
{
	if (pipe(pipefd) == -1)
	{
		ft_dprintf(STDERR_FILENO, ERR_PIPE, strerror(errno));
		return (false);
	}
	return (true);
}
