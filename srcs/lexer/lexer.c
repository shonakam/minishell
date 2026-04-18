#include "lexer_internal.h"

static void	skip_spaces(char **line, t_qstate state)
{
	if (state != QUOTE_NONE)
		return ;
	while (**line && ft_is_whitespace(**line))
		(*line)++;
}

static bool	add_token(t_list **list, t_token *t)
{
	t_list	*node;

	if (!t)
		return (false);
	node = x_lstnew(t);
	if (!node)
		return (token_free(t), false);
	ft_lstadd_back(list, node);
	return (true);
}

static bool	add_terminator_tokens(t_list **tokens)
{
	t_token	*newline;
	t_token	*eof;

	newline = token_new(TOKEN_NEWLINE, QUOTE_NONE, x_strdup("\n"));
	if (!add_token(tokens, newline))
		return (false);
	eof = token_new(TOKEN_EOF, QUOTE_NONE, x_strdup(""));
	if (!add_token(tokens, eof))
		return (false);
	return (true);
}

/*
 * Tokenizes the input string into a list of t_token structures.
 *
 * This lexer scans the input character by character and performs:
 * 1. Skipping whitespaces (outside of quotes).
 * 2. Identifying control operators (e.g., |, ;, &&, ||, (, )).
 * 3. Handling words, supporting single (') and double (") quotes.
 * 4. Validating basic lexical syntax (e.g., unclosed quotes).
 * 5. Appending NEWLINE and EOF tokens to mark the end of the command list.
 *
 * Returns a pointer to the head of the token list.
 * Returns NULL if memory allocation fails, or if lexical errors are detected.
 */
t_list	*lexer(char	*line)
{
	t_list			*tokens;
	t_token			*t;
	t_qstate		state;

	tokens = NULL;
	state = QUOTE_NONE;
	while (*line)
	{
		skip_spaces(&line, state);
		if (!*line)
			break;
		if (state == QUOTE_NONE && is_operator(line))
			t = handle_operator(&line, is_operator(line));
		else
			t = handle_word(&line, &state);
		if (!add_token(&tokens, t))
			return (ft_lstclear(&tokens, token_free), NULL);
	}
	if (!is_syntax_valid(state))
		return (ft_lstclear(&tokens, token_free), NULL);
	if (!add_terminator_tokens(&tokens))
        return (ft_lstclear(&tokens, token_free), NULL);
	return (tokens);
}
