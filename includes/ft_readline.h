#ifndef FT_READLINE_H
# define FT_READLINE_H

# include "libft.h"
# include "session.h"
# include "utils.h"

bool	termios_ctl(bool is_init);
char	*ft_readline(const char *prompt);
void	ft_load_history(void);
void	ft_add_history(const char *line);
void	ft_history_destroy(void);

#endif /* FT_READLINE_H */
