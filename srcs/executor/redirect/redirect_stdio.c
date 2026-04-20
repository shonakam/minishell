#include "../executor_internal.h"

bool	save_stdio(t_context *ctx)
{
	ctx->fd_save[0] = x_dup(STDIN_FILENO);
	if (ctx->fd_save[0] == -1)
		return (false);
	ctx->fd_save[1] = x_dup(STDOUT_FILENO);
	if (ctx->fd_save[1] == -1)
	{
		close(ctx->fd_save[0]);
		ctx->fd_save[0] = -1;
		return (false);
	}
	return (true);
}

static void	restore_specific_fd(int *saved_fd, int target_fd)
{
	if (*saved_fd != -1)
	{
		x_dup2(*saved_fd, target_fd);
		close(*saved_fd);
		*saved_fd = -1;
	}
}

void	restore_stdio(t_context *ctx)
{
	restore_specific_fd(&ctx->fd_save[0], STDIN_FILENO);
	restore_specific_fd(&ctx->fd_save[1], STDOUT_FILENO);
}
