#ifndef LEXER_H
# define LEXER_H

# include <stdbool.h>
# include "libft.h"

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

typedef enum e_token_state {
	TOKEN_NONE = 0,
	TOKEN_IN_SINGLE,
	TOKEN_IN_DOUBLE,
	TOKEN_IN_WORD,
	TOKEN_STATE_SIZE
}   t_token_state;

typedef struct s_token {
	t_token_type	type;
	t_token_state	state;
	char			*str;
}	t_token;

t_list			*lexer(char *line);

// t_token			*token_new(t_token_type type, t_token_state state, char *str);
void			token_free(void *content);
bool			token_append(t_list **list, t_token *t);
t_token			*token_consume(t_list **tokens);
t_token			*token_peek(t_list **tokens);
t_token_type	token_peek_type(t_list **tokens);
t_token_type	token_get_type(const char *str);

#endif /* LEXER_H */
