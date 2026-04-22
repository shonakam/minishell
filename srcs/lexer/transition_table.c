#include "lexer_internal.h"

static void	init_none_state(t_trans_matrix table)
{
	table[TOKEN_NONE][EV_SPACE] = act_ignore;
	table[TOKEN_NONE][EV_SQUOTE] = act_quote_open;
	table[TOKEN_NONE][EV_DQUOTE] = act_quote_open;
	table[TOKEN_NONE][EV_META] = act_handle_meta;
	table[TOKEN_NONE][EV_DOLLAR] = act_handle_dollar;
	table[TOKEN_NONE][EV_CHAR] = act_add_and_word;
	table[TOKEN_NONE][EV_EOF] = act_end_of_file;
}

static void	init_word_state(t_trans_matrix table)
{
	table[TOKEN_IN_WORD][EV_SPACE] = act_delimiter;
	table[TOKEN_IN_WORD][EV_SQUOTE] = act_quote_open;
	table[TOKEN_IN_WORD][EV_DQUOTE] = act_quote_open;
	table[TOKEN_IN_WORD][EV_META] = act_delimiter;
	table[TOKEN_IN_WORD][EV_DOLLAR] = act_handle_dollar;
	table[TOKEN_IN_WORD][EV_CHAR] = act_add_char;
	table[TOKEN_IN_WORD][EV_EOF] = act_delimiter;
}

static void	init_single_quote_state(t_trans_matrix table)
{
	table[TOKEN_IN_SINGLE][EV_SPACE] = act_add_char;
	table[TOKEN_IN_SINGLE][EV_SQUOTE] = act_quote_close;
	table[TOKEN_IN_SINGLE][EV_DQUOTE] = act_add_char;
	table[TOKEN_IN_SINGLE][EV_META] = act_add_char;
	table[TOKEN_IN_SINGLE][EV_DOLLAR] = act_add_char;
	table[TOKEN_IN_SINGLE][EV_CHAR] = act_add_char;
	table[TOKEN_IN_SINGLE][EV_EOF] = act_err_unclosed;
}

static void init_double_quote_state(t_trans_matrix table)
{
	table[TOKEN_IN_DOUBLE][EV_SPACE] = act_add_char;
	table[TOKEN_IN_DOUBLE][EV_SQUOTE] = act_add_char;
	table[TOKEN_IN_DOUBLE][EV_DQUOTE] = act_quote_close;
	table[TOKEN_IN_DOUBLE][EV_META] = act_add_char;
	table[TOKEN_IN_DOUBLE][EV_DOLLAR] = act_add_char;
	table[TOKEN_IN_DOUBLE][EV_CHAR] = act_add_char;
	table[TOKEN_IN_DOUBLE][EV_EOF] = act_err_unclosed;
}

t_trans_matrix	*get_transition_table(void)
{
	static t_trans_matrix table;
	static bool           is_initialized = false;
	if (is_initialized)
		return (&table);
	init_none_state(table);
    init_word_state(table);
    init_single_quote_state(table);
    init_double_quote_state(table);
	is_initialized = true;
	return (&table);
}
