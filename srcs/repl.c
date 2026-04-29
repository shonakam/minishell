#include "minishell.h"
#include "ft_readline.h"
#include "error.h"
#include "session.h"
#include "lexer.h"
#include "parser.h"
#include "executor.h"
#include "builtin.h"
#include "utils.h"

static bool	should_continue(t_context *ctx)
{
	if (ctx->exit)
		return (false);
	if (!ctx->scope.line && g_signal_flag != SIGINT)
		return (false);
	if (g_signal_flag == SIGINT)
	{
		g_signal_flag = 0;
		return (true);
	}
	return (true);
}

unsigned int	repl(t_context *ctx)
{
	while (true)
	{
		signal_set_mode(SIG_MODE_IDLE);
		scope_init(&ctx->scope);
		job_sync(ctx);
		ctx->scope.line = ft_readline(PS1);
		if (!should_continue(ctx))
			break ;
		if (!ctx->scope.line)
			continue ;
		if (*ctx->scope.line)
		{
			ft_add_history((const char *)ctx->scope.line);
			ctx->scope.tokens = lexer(ctx->scope.line);
			ctx->scope.tokens_anchor = ctx->scope.tokens;
			debug_print_list(ctx->scope.tokens, debug_print_token);
			ctx->scope.ast = parser(ctx, &ctx->scope.tokens);
			debug_print_ast(ctx->scope.ast);
			executor(ctx, ctx->scope.ast);
		}
		scope_clear(&ctx->scope);
	}
	return (ctx->last_status);
}
