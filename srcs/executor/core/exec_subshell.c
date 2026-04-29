#include "../executor_internal.h"

static void	wait_and_cleanup_job(t_context *ctx)
{
	signal_set_mode(SIG_MODE_EXEC);
	job_wait(ctx, ctx->job.all);
	job_clear_all(ctx);
	signal_set_mode(SIG_MODE_IDLE);
}

static void	run_subshell_child(t_context *ctx, t_ast_node *node)
{
	termios_ctl(false);
	signal_set_mode(SIG_MODE_CHILD);
	job_free(ctx->job.current);
	ctx->job.current = NULL;
	pipeline_connect_io(ctx);
	if (node->redirects && !redirect_apply(node->redirects))
		safe_exit(ctx, NULL, NULL, EXIT_FAILURE);
	ctx->in_pipeline = false;
	traverse_ast(ctx, node->left);
	safe_exit(ctx, NULL, NULL, ctx->last_status);
}

void	exec_subshell(t_context *ctx, t_ast_node *node)
{
	pid_t	pid;
	bool	saved_in_pipeline;

	saved_in_pipeline = ctx->in_pipeline;
	ctx->subshell_depth++;
	if (saved_in_pipeline)
		run_subshell_child(ctx, node);
	else
	{
		if (x_fork(&pid) && pid == 0)
			run_subshell_child(ctx, node);
		if (!ctx->job.current)
		{
			ctx->job.current = job_new(get_next_job_id(ctx), "(sub)", false);
			job_register(ctx, ctx->job.current);
		}
		job_add_pid(ctx->job.current, pid);
		wait_and_cleanup_job(ctx);
	}
	ctx->subshell_depth--;
}
