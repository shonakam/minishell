#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdbool.h>
# include "libft.h"
# include "session.h"

# define PROGRAM_NAME "minishell"

/* Prompt String */
# define PS1 "minishell$ "
# define PS2 "> "

/* Exit statuses for shell commands */
#define STATUS_SUCCESS				0
#define STATUS_GENERAL_ERROR		1
#define STATUS_SYNTAX_ERR			2   /* Bash standard for syntax errors */
#define STATUS_CANNOT_EXECUTE		126 /* Command found but not executable */
#define STATUS_COMMAND_NOT_FOUND	127 /* Command not found in PATH */
#define STATUS_SIGNAL_INTERRUPT		128 /* Base for signal-related exits (128 + sig) */
#define STATUS_FATAL_ERROR          255 /* Exit status out of range or numeric argument required */

unsigned int	repl(t_context *ctx);

#endif /* MINISHELL_H */
