#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <string.h>
# include <errno.h>
# include <stdbool.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>

# include "../srcs/libft/libft.h"

# include "token.h"
# include "parser.h"
# include "envlist.h"
# include "support.h"
# include "../srcs/test/test.h"

typedef struct	s_minishell	{
	char		*line;
	// char		**bin_path;
	t_envlist	*envlist;
	t_token		**token;
	t_command	*cmd;
}				t_minishell;

t_token		**ft_lexer(char *line);
t_command	*build_commands(t_token **tokens, int count);

int			ft_exec(t_minishell *mini);
void		ft_clean(t_minishell *mini, int flag);
void		ft_clean_exit(t_minishell *mini);


#endif
