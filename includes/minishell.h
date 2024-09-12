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

# include "libft/libft.h"
# include "token.h"
# include "parser.h"
# include "envlist.h"
# include "cmd.h"
# include "support.h"

// # include "test/test.h"

# define READ	0
# define WRITE	1

typedef struct	s_minishell	{
	char		*line;
	t_envlist	*envlist;
	t_token		**token;
	t_command	*cmd;
	int			status;
}				t_minishell;

t_token		**ft_lexer(char *line);
char		*resolve_eos(char *line);
t_command	*build_commands(t_token **tokens, int count);
// void		ft_exec_v1(t_minishell *mini);
void		ft_exec_v3(t_minishell *mini);

int			get_exit_status(t_minishell *mini);
void		ft_clean(t_minishell *mini, int flag);
void		ft_clean_exit(t_minishell *mini);

#endif
