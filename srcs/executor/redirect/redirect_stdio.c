#include "../executor_internal.h"

static bool	save_stdfds(int stdfds[2])
{
	stdfds[0] = x_dup(STDIN_FILENO);
	if (stdfds[0] == -1)
		return (false);
	stdfds[1] = x_dup(STDOUT_FILENO);
	if (stdfds[1] == -1)
	{
		close(stdfds[0]);
		stdfds[0] = -1;
		return (false);
	}
	return (true);
}

static void	restore_stdfds(int stdfds[2])
{
	if (stdfds[0] != -1)
	{
		x_dup2(stdfds[0], STDIN_FILENO);
		close(stdfds[0]);
		stdfds[0] = -1;
	}
	if (stdfds[1] != -1)
	{
		x_dup2(stdfds[1], STDOUT_FILENO);
		close(stdfds[1]);
		stdfds[1] = -1;
	}
}

bool	stdio_manager(int stdfds[2], bool restore)
{
	if (restore)
	{
		restore_stdfds(stdfds);
		return (true);
	}
	return (save_stdfds(stdfds));
}
