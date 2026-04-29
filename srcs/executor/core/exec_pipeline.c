#include "../executor_internal.h"

static void	pipeline_loop(t_context *ctx, t_ast_node **cmds, int n)
{
	t_pipeline_manager	pm;
	int					orig_io[2];

	pm.i = 0;
	orig_io[0] = ctx->scope.fd_stdio[0];
	orig_io[1] = ctx->scope.fd_stdio[1];
	pm.pr_fd = orig_io[0];
	while (pm.i < n)
	{
		if (pm.i < n - 1 && !x_pipe(pm.p))
			break ;
		prepare_pipe_fds(ctx, &pm, orig_io[1], n);
		if (x_fork(&pm.pid) && pm.pid == 0)
		{
			if (pm.i < n - 1)
				close(pm.p[0]);
			pipeline_connect_io(ctx);
			oneshot(ctx, cmds[pm.i]);
		}
		update_pipe_state(ctx, &pm, pm.i++, n);
	}
	if (orig_io[1] != ctx->scope.fd_stdio[1] && orig_io[1] > STDERR_FILENO)
		close(orig_io[1]);
	ctx->scope.fd_stdio[0] = orig_io[0];
}

static void	pipeline_wrap_up(
	t_context *ctx, t_ast_node **cmds, bool prev_in, int n)
{
	signal_set_mode(SIG_MODE_EXEC);
	job_register(ctx, ctx->job.current);
	pipeline_loop(ctx, ctx->scope.sub_root, n);
	if (ctx->in_pipeline)
		job_wait(ctx, ctx->job.current);
	job_discard(ctx, ctx->job.current);
	ctx->in_pipeline = prev_in;
	free(cmds);
	ctx->scope.sub_root = NULL;
	signal_set_mode(SIG_MODE_IDLE);
}

void	exec_pipeline(t_context *ctx, t_ast_node *node)
{
	int			n;
	char		*cmd_line;
	bool		prev_in;
	t_ast_node	**cmds;

	n = 0;
	cmds = NULL;
	flatten_pipeline(node, &cmds, &n);
	if (!cmds)
		return ;
	ctx->scope.sub_root = cmds;
	cmd_line = ast_to_str(node);
	ctx->job.current = job_new(get_next_job_id(ctx), cmd_line, false);
	free(cmd_line);
	prev_in = ctx->in_pipeline;
	ctx->in_pipeline = true;
	pipeline_wrap_up(ctx, cmds, prev_in, n);
}
