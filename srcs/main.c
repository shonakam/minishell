#include "minishell.h"

volatile sig_atomic_t	g_signal_flag = 0;

unsigned int repl(t_context *ctx)
{
	char		*line;
	t_list		*tokens;
	// t_command	*commands;

	while (true)
	{
		signal_set_mode(SIG_MODE_IDLE);
		line = readline("minishell$ ");
		if (!line)
			break ;
		if (*line)
		{
			add_history(line);
			tokens = lexer(line);
			// commands = parser(tokens);
			// 1. lexer: line -> t_list *tokens
			// 2. parser: tokens -> t_node *tree
			// 3. executor: tree -> execution (using ctx->env_list)
			debug_print_list(tokens, debug_show_token);
			ft_lstclear(&tokens, token_free);
		}
		free(line);
	}
	return (ctx->last_status);
}

int	main(int ac, char **av, char **envp)
{
	t_context	ctx;
	int			status;

	(void)ac;
	(void)av;
	if (!context_init(&ctx, envp))
		return (EXIT_FAILURE);
	status = repl(&ctx);
	context_destroy(&ctx);
	return (status);
}
