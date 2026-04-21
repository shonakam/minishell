#include "session_internal.h"

/*
* signal_set_mode:
* Manages signal configurations for both parent and child processes.
*
* SIG_MODE_IDLE: Configures handlers for the interactive prompt.
* SIG_MODE_EXEC: Makes the parent ignore signals while waiting for children.
* SIG_MODE_CHILD: Resets signals to their default behavior for executed commands.
*/
void	signal_set_mode(t_sig_mode mode)
{
	if (mode == SIG_MODE_IDLE)
	{
		signal(SIGINT, sig_handle_idle_int);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (mode == SIG_MODE_HEREDOC)
	{
		signal(SIGINT, sig_handle_heredoc_int);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (mode == SIG_MODE_EXEC)
	{
		signal(SIGINT, sig_handle_blocking_int);
		signal(SIGQUIT, sig_handle_blocking_quit);
	}
	else if (mode == SIG_MODE_CHILD)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
	}
	else if (mode == SIG_MODE_BACKGROUND)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
}
