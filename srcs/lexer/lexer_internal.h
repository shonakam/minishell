#ifndef LEXER_INTERNAL_H
# define LEXER_INTERNAL_H

# include <stdbool.h>
# include "libft.h"
# include "error.h"
# include "lexer.h"
# include "utils.h"

typedef enum e_char_event {
	EV_SPACE = 0,
	EV_SQUOTE,
	EV_DQUOTE,
	EV_META,
	EV_DOLLAR,
	EV_CHAR,
	EV_EOF,
	EV_MAX
}	t_char_event;

typedef struct s_lexer t_lexer;
typedef void	(*t_action)(t_lexer *l, t_token_state *state);
typedef t_action t_trans_matrix[TOKEN_STATE_SIZE][EV_MAX];

typedef struct s_lexer {
	const char		*input;
	size_t			pos;
	char			ch;
	char			*buffer;
	size_t			buf_size;
	size_t			buf_idx;
	t_token_type	current_type;
	t_token_state   quote_state;
	bool			is_token_finished;
	bool			is_err;
	t_trans_matrix	*table;
}	t_lexer;


// lexer_actions_common.c
void	act_add_char(t_lexer *l, t_token_state *next);
void	act_ignore(t_lexer *l, t_token_state *next);
void	act_delimiter(t_lexer *l, t_token_state *next);
void	act_end_of_file(t_lexer *l, t_token_state *next);
void	act_add_and_word(t_lexer *l, t_token_state *next);
// lexer_actions_special.c
void	act_handle_meta(t_lexer *l, t_token_state *next);
void	act_err_unclosed(t_lexer *l, t_token_state *next);
void	act_handle_dollar(t_lexer *l, t_token_state *next);
// lexer_actions_state.c
void	act_quote_open(t_lexer *l, t_token_state *next);
void	act_quote_close(t_lexer *l, t_token_state *next);

t_trans_matrix	*get_transition_table(void);
t_token	*token_new(t_lexer *l);
t_token	*token_create(
	t_token_type type, t_token_state state, const char *str);
t_token	*tokenize_stream(t_lexer *l);
void	lexer_advance(t_lexer *l);
char	lexer_peek(t_lexer *l);
void	lexer_reset_buffer(t_lexer *l);

#endif /* LEXER_INTERNAL_H */
