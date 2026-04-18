#ifndef LEXER_INTERNAL_H
# define LEXER_INTERNAL_H

# include "error.h"
# include "lexer.h"

t_token			*token_new(t_token_type type, t_qstate state, char *str);
t_token_type	get_token_type(const char *str);
void			fsm(t_qstate *state, char c);
t_token			*handle_operator(char **line, int op_len);
t_token			*handle_word(char **line, t_qstate *state);
bool			is_syntax_valid(t_qstate state);

#endif /* LEXER_INTERNAL_H */
