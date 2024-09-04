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
# include "ast.h"

t_token		**ft_lexer(char *line);
t_command	*build_commands(t_token **tokens, int count);
int			ft_exec(t_token **tokens);

#endif
