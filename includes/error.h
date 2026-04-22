#ifndef ERROR_H
# define ERROR_H

# include <errno.h>
# include <string.h>
# include "minishell.h"

# define MSG_SHLVL_WARN PROGRAM_NAME \
	": warning: shell (%d) level too high, resetting to 1\r\n"

/* --- Syntax Errors (Lexer/Parser) --- */
# define ERR_QUOTE_EOF  PROGRAM_NAME \
	": unexpected EOF while looking for matching `%c'\r\n"
# define ERR_SYNTAX_EOF PROGRAM_NAME \
	": syntax error: unexpected end of file\r\n"
# define ERR_SYNTAX_TOKEN PROGRAM_NAME \
	": syntax error near unexpected token `%s'\r\n"

/* --- Heredoc --- */
# define ERR_HEREDOC_EOF PROGRAM_NAME \
    ": warning: here-document at line %d delimited by end-of-file (wanted `%s')\r\n"

/* --- System・Resource --- */
// set errno
# define ERR_MALLOC     PROGRAM_NAME \
	": fatal: memory allocation failed\n"
# define ERR_DUP    	PROGRAM_NAME ": dup error: %s\r\n"
# define ERR_DUP2    	PROGRAM_NAME ": dup2 error: %s\r\n"
# define ERR_PIPE       PROGRAM_NAME ": pipe error: %s\r\n"
# define ERR_FORK       PROGRAM_NAME ": fork error: %s\r\n"
# define ERR_EXECVE     PROGRAM_NAME ": %s: %s\r\n"
# define ERR_OPEN       PROGRAM_NAME ": %s: %s\r\n"

/* --- Execute Error --- */
# define ERR_CMD_NOT_FOUND	PROGRAM_NAME ": %s: command not found\r\n"
# define ERR_NO_FILE 	PROGRAM_NAME ": %s: No such file or directory\r\n"
# define ERR_IS_DIR 	PROGRAM_NAME ": %s: Is a directory\r\n"
# define ERR_PERMISSION PROGRAM_NAME ": %s: Permission denied\r\n"

/* --- Builtin --- */
# define ERR_TOO_MANY_ARGS	PROGRAM_NAME ": %s: too many arguments\r\n"
# define ERR_EXIT_NUMERIC	PROGRAM_NAME \
	": exit: %s: numeric argument required\r\n"
# define ERR_CD_HOME		PROGRAM_NAME ": cd: HOME not set\r\n"
# define ERR_CD_OLDPWD		PROGRAM_NAME ": cd: OLDPWD not set\r\n"
# define ERR_PWD_GETCWD		PROGRAM_NAME \
	": pwd: error retrieving current directory:\
	getcwd: cannot access parent directories\r\n"

# define ERR_INVALID_ID 		PROGRAM_NAME \
	": export: `%s': not a valid identifier\r\n"
# define ERR_INVALID_ID_UNSET	PROGRAM_NAME \
	": unset: `%s': not a valid identifier\r\n"

#endif /* ERROR_H */
