#ifndef SESSION_INTERNAL_H
# define SESSION_INTERNAL_H

# include <sys/ioctl.h>
# include "session.h"
# include "builtin.h"
# include "executor.h"
# include "error.h"
# include "utils.h"

# define KEY_SHLVL "SHLVL"
# define SHLVL_MAX 1000
# define SHLVL_DEFAULT "1"

bool	update_shlvl(t_list *lst);
void	sig_handle_idle_int(int sig);
void	sig_handle_heredoc_int(int sig);
void	sig_handle_blocking_int(int sig);
void	sig_handle_blocking_quit(int sig);

#endif /* SESSION_INTERNAL_H */
