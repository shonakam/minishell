#include "../executor_internal.h"

/**
 * Determines if the command should be executed in a separate process.
 * 1. External commands: Always require fork for execve.
 * 2. Pipeline: Each command must run in parallel within its own process.
 * 3. Background: Must fork to prevent the main shell from blocking.
 * Otherwise (e.g., a single builtin command),
 * it executes in the current process.
 */
static bool	should_fork(t_context *ctx, t_builtin_func builtin)
{
	if (ctx->in_pipeline)
		return (true);
	if (builtin == NULL)
		return (true);
	if (ctx->job.current && ctx->job.current->is_background)
		return (true);
	return (false);
}

static char	*get_cmd_name(t_list *args)
{
	if (!args || !args->content)
		return (NULL);
	return (((t_arg *)args->content)->str);
}

void	exec_builtin_main(
	t_context *ctx, t_simple_command *cmd, t_builtin_func func)
{
	char	**argv;
	int		local[2];

	if (!stdio_manager(local, false))
		return ;
	if (expand_command(ctx, cmd) && redirect_apply(cmd->redirects))
	{
		argv = convert_args_to_argv(cmd->args);
		if (argv)
		{
			ctx->last_status = func(ctx, argv);
			free_matrix(argv);
		}
	}
	else
		ctx->last_status = EXIT_FAILURE;
	stdio_manager(local, true);
}

static void	exec_external_parent(t_context *ctx, t_ast_node *node, pid_t pid)
{
	t_job	*job;
	char	*cmd_line;

	cmd_line = ast_to_str(node);
	job = job_new(get_next_job_id(ctx), cmd_line, false);
	if (!job)
		return ((void)free(cmd_line));
	free(cmd_line);
	job_add_pid(job, pid);
	job_register(ctx, job);
	if (!ctx->in_pipeline)
	{
		signal_set_mode(SIG_MODE_EXEC);
		job_wait(ctx, job);
		signal_set_mode(SIG_MODE_IDLE);
	}
}

/**
 * Entry point for executing a Simple Command.
 * Routes execution to either the child process (oneshot) or the
 * main process (builtin), ensuring pipelines are handled correctly.
 */
void	exec_command(t_context *ctx, t_ast_node *node)
{
	t_simple_command	*cmd;
	t_builtin_func		builtin;
	pid_t				pid;

	if (ctx->in_pipeline)
		oneshot(ctx, node);
	cmd = node->data.command;
	builtin = get_builtin_func(ctx, get_cmd_name(cmd->args));
	if (!should_fork(ctx, builtin))
		return (exec_builtin_main(ctx, cmd, builtin));
	if (x_fork(&pid) && pid == 0)
		oneshot(ctx, node);
	exec_external_parent(ctx, node, pid);
}
