#include "minishell.h"
#include "ft_readline.h"
#include "session.h"
#include "lexer.h"
#include "parser.h"
#include "executor.h"

volatile sig_atomic_t	g_signal_flag = 0;

int	main(int ac, char **av, char **envp)
{
	t_context	ctx;
	int			status;

	(void)ac;
	(void)av;
	termios_ctl(true);
	signal(SIGPIPE, SIG_IGN);
	ft_load_history();
	if (!context_init(&ctx, envp))
		return (EXIT_FAILURE);
	status = repl(&ctx);
	termios_ctl(false);
	ft_history_destroy();
	context_destroy(&ctx);
	return (status);
}
