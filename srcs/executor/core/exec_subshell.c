#include "../executor_internal.h"

static void wait_and_cleanup_job(t_context *ctx)
{
	signal_set_mode(SIG_MODE_EXEC);
	job_wait(ctx, ctx->job.current);
	job_free(ctx->job.current);
	ctx->job.current = NULL;
	signal_set_mode(SIG_MODE_IDLE);
}

static void run_subshell_child(t_context *ctx, t_ast_node *node)
{
	termios_ctl(false);
	signal_set_mode(SIG_MODE_CHILD);
	if (node->redirects && !redirect_apply(node->redirects))
		safe_exit(ctx, NULL, NULL, EXIT_FAILURE);
	exec_engine(ctx, node->left);
	if (ctx->job.current)
    {
        job_free(ctx->job.current);
        ctx->job.current = NULL;
    }
	safe_exit(ctx, NULL, NULL, ctx->last_status);
}

void	exec_subshell(t_context *ctx, t_ast_node *node)
{
	pid_t	pid;

	if (x_fork(&pid) && pid == 0)
		run_subshell_child(ctx, node);
	if (!ctx->job.current)
		ctx->job.current = job_new(get_next_job_id(ctx), "(subshell)", false);
	if (ctx->job.current)
		job_add_pid(ctx->job.current, pid);
	if (!ctx->in_pipeline && ctx->job.current)
		wait_and_cleanup_job(ctx);
}
