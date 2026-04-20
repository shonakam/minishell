#include "../executor_internal.h"

void	exec_subshell(t_context *ctx, t_ast_node *node)
{
	pid_t	pid;

	if (x_fork(&pid) && pid == 0)
	{
		signal_set_mode(SIG_MODE_CHILD);
		if (node->data.command &&
				!redirect_apply(node->data.command->redirects))
			exit(EXIT_FAILURE);
		exec_engine(ctx, node->left);
		exit(ctx->last_status);
	}
	job_add_pid(ctx->job.current, pid);
	if (!ctx->in_pipeline)
	{
		signal_set_mode(SIG_MODE_EXEC);
		job_wait(ctx, ctx->job.current);
		signal_set_mode(SIG_MODE_IDLE);
    }
}
