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
# include "support.h"
# include "envlist.h"
# include "ast.h"

// typedef struct s_envlist
// {
// 	char				*env_var;
// 	char				*value;
// 	struct s_envlist	*next;
// }				t_envlist;


t_token	**ft_lexer(char *line);

int	ft_exec(t_token **tokens);

#endif
