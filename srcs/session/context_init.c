#include "session_internal.h"

static bool	termios_init(t_context *ctx)
{
	if (tcgetattr(STDIN_FILENO, &ctx->original) == -1)
        return (false);
    ctx->current = ctx->original;
    ctx->current.c_lflag &= ~ECHOCTL;
    tcsetattr(STDIN_FILENO, TCSANOW, &ctx->current);
    return (true);
}

static void close_saved_fds(t_context *ctx)
{
	if (ctx->fd_save[0] != -1)
		close(ctx->fd_save[0]);
	if (ctx->fd_save[1] != -1)
		close(ctx->fd_save[1]);
	ctx->fd_save[0] = -1;
	ctx->fd_save[1] = -1;
}

bool	context_init(t_context *ctx, char **envp)
{
	ft_memset(ctx, 0, sizeof(t_context));
	ctx->job.next_id = 1;
	ctx->fd_save[0] = x_dup(STDIN_FILENO);
	ctx->fd_save[1] = x_dup(STDOUT_FILENO);
	if (ctx->fd_save[0] == -1 || ctx->fd_save[1] == -1)
		return (close_saved_fds(ctx), false);
	if (!termios_init(ctx))
        return (close_saved_fds(ctx), false);
	ctx->env_list = env_load(envp);
	if (!ctx->env_list)
		return (false);
	if (!update_shlvl(ctx->env_list))
		return (false);
	if (!builtin_table_init(ctx))
		return (false);
	ctx->last_status = 0;
	return (true);
}
