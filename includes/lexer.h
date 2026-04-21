#ifndef LEXER_H
# define LEXER_H

# define OPERATOR_CHARS "|<>();&"
# define OP_HEREDOC "<<"
# define OP_APPEND  ">>"
# define OP_AND_IF  "&&"
# define OP_OR_IF   "||"

typedef enum e_token_type {
	TOKEN_WORD,         // ls, -l, filename
	TOKEN_SEMICOLON,    // ;
	TOKEN_NEWLINE,      // \n
	TOKEN_PIPE,         // |
	TOKEN_REDIRECT_IN,  // <
	TOKEN_REDIRECT_OUT, // >
	TOKEN_APPEND,       // >>
	TOKEN_HEREDOC,      // <<
	TOKEN_AND_IF,       // &&
	TOKEN_OR_IF,        // ||
	TOKEN_AMPERSAND,    // &
	TOKEN_LPAREN,       // (
	TOKEN_RPAREN,       // )
	TOKEN_EOF
}	t_token_type;

typedef enum e_qstate {
	QUOTE_NONE = 0,
	QUOTE_SINGLE,
	QUOTE_DOUBLE
}   t_qstate;

typedef struct s_token {
	t_token_type	type;
	t_qstate		state;
	char			*str;
}	t_token;

typedef enum e_status {
    STATUS_OK,          /* Success: Lexing completed normally */
    STATUS_INCOMPLETE,  /* Incomplete: Needs more input (multiline/prompt) */
    STATUS_ERROR,       /* Syntax Error: Error message already printed via dprintf */
    STATUS_FATAL        /* Fatal Error: Critical failure (e.g., memory allocation) */
}	t_status;

typedef struct s_lexer_result {
    t_status	status;
    t_list		*tokens;  /* Contains the token list only if status is STATUS_OK */
}	t_lexer_result;

t_list			*lexer(char *line);
void			token_free(void *content);

#endif /* LEXER_H */
