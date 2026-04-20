#include "session_internal.h"

/*
 * Checks if the child process was terminated by a signal.
 * If terminated by SIGQUIT (Ctrl+\), prints "Quit: 3" & checks for core dump.
 * If terminated by SIGINT (Ctrl+C), prints a newline to match Bash 5 behavior.
 */
void	signal_check_child(char *args, int status)
{
	if (WIFSIGNALED(status))
    {
        int sig = WTERMSIG(status);

        if (sig == SIGQUIT)
        {
            ft_putstr_fd("^\\Quit: 3", STDOUT_FILENO);
            if (WCOREDUMP(status))
                ft_putstr_fd(" (core dumped)", STDOUT_FILENO);
            ft_putstr_fd("		", STDOUT_FILENO);
            if (args)
                ft_putendl_fd(args, STDOUT_FILENO);
            else
                ft_putendl_fd("", STDOUT_FILENO);
        }
        else if (sig == SIGINT)
        {
            ft_putendl_fd("", STDOUT_FILENO);
        }
    }
}
