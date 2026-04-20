#include "../executor_internal.h"

/**
 * Determines if the command should be executed in a separate process.
 * 1. External commands: Always require fork for execve.
 * 2. Pipeline: Each command must run in parallel within its own process.
 * 3. Background: Must fork to prevent the main shell from blocking.
 * Otherwise (e.g., a single builtin command), it executes in the current process.
 */
bool	should_fork(t_context *ctx, t_builtin_func builtin)
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

static void in_main_process(
	t_context *ctx, t_simple_command *cmd, t_builtin_func builtin)
{
	char	**argv;

	save_stdio(ctx);
	if (expand_command(ctx, cmd) && redirect_apply(cmd->redirects))
	{
		if (cmd->args)
		{
			builtin = get_builtin_func(ctx, get_cmd_name(cmd->args));
			argv = convert_args_to_argv(cmd->args);
			if (argv)
			{
				ctx->last_status = builtin(ctx, argv);
				free_matrix(argv);
			}
		}
	}
	else
	{
		ctx->last_status = EXIT_FAILURE;
	}
	restore_stdio(ctx);
}

void	exec_command(t_context *ctx, t_ast_node *node)
{
	t_simple_command	*cmd;
	t_builtin_func		builtin;
	char				*cmd_line;
	pid_t				pid;

	cmd = node->data.command;
	builtin = get_builtin_func(ctx, get_cmd_name(cmd->args));
	if (ctx->in_pipeline)
		return ((void)oneshot(ctx, node));
	if (!should_fork(ctx, builtin))
		return ((void)in_main_process(ctx, cmd, builtin));
	cmd_line = ast_to_str(node);
	ctx->job.current = job_create(ctx, cmd_line, false);
	free(cmd_line);
	if (x_fork(&pid) && pid == 0)
		oneshot(ctx, node);

	signal_set_mode(SIG_MODE_EXEC);
	job_add_pid(ctx->job.current, pid);
	job_wait(ctx, ctx->job.current);
	signal_set_mode(SIG_MODE_IDLE);

	ctx->job.current = NULL;
}
