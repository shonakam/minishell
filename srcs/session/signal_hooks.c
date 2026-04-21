#include "session_internal.h"

void	sig_handle_idle_int(int sig)
{
	(void)sig;
	g_signal_flag = SIGINT;
	ft_putstr_fd("\r", STDOUT_FILENO);
	ft_putstr_fd(PS1, STDOUT_FILENO);
	ft_putstr_fd("^C\033[K", STDOUT_FILENO);
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
}

void	sig_handle_heredoc_int(int sig)
{
	(void)sig;
	g_signal_flag = SIGINT;
	ft_putstr_fd("\r", STDOUT_FILENO);
	ft_putstr_fd(PS2, STDOUT_FILENO);
	ft_putstr_fd("^C\033[K", STDOUT_FILENO);
	ioctl(STDIN_FILENO, TIOCSTI, "\x04");
}

void	sig_handle_blocking_int(int sig)
{
	(void)sig;
	g_signal_flag = SIGINT;
	write(STDOUT_FILENO, "^C\n", 3);
}

void	sig_handle_blocking_quit(int sig)
{
	(void)sig;
	g_signal_flag = SIGQUIT;
}
