#include "lexer_internal.h"

static void	*lexer_cleanup(t_lexer *l, t_list **tokens)
{
	if (l->buffer)
		free(l->buffer);
	return (ft_lstclear(tokens, token_free), NULL);
}

static bool	lexer_setup(t_lexer *l, char *line)
{
	if (!line || !l)
		return (false);
	ft_memset(l, 0, sizeof(t_lexer));
	l->input = line;
	l->ch = line[0];
	l->buf_size = BUFFER_SIZE;
	l->buffer = x_calloc(l->buf_size, sizeof(char));
	if (!l->buffer)
		return (false);
	l->table = get_transition_table();
	if (!l->table)
		return (false);
	return (true);
}

static t_list	*lexer_finelize(t_lexer *l, t_list **tokens)
{
	t_token	*token;
	t_list	*node;

	token = token_create(TOKEN_NEWLINE, TOKEN_NONE, "newline");
	if (!token)
		return (lexer_cleanup(l, tokens));
	node = x_lstnew(token);
	if (!node)
		return (token_free(token), lexer_cleanup(l, tokens));
	ft_lstadd_back(tokens, node);
	token = token_create(TOKEN_EOF, TOKEN_NONE, "EOF");
	if (!token)
		return (lexer_cleanup(l, tokens));
	node = x_lstnew(token);
	if (!node)
		return (token_free(token), lexer_cleanup(l, tokens));
	ft_lstadd_back(tokens, node);
	free(l->buffer);
	return (*tokens);
}

/*
 * Tokenizes the input string into a list of t_token structures using a
 * Finite State Machine (FSM) approach.
 *
 * The lexer scans the input character by character, managing state transitions
 * to perform the following:
 * 1. Skips whitespaces outside of quotes.
 * 2. Identifies control operators (e.g., |, <, >, &&, ||).
 * 3. Handles special parameters (e.g., $?) as distinct tokens or within words.
 * 4. Supports literal protection via single (') and double (") quotes.
 * 5. Validates lexical syntax, such as detecting unclosed quotes.
 * 6. Aborts processing and reports errors
 *    via the is_err flag if syntax is invalid.
 *
 * Returns a pointer to the head of the t_list containing t_token structures.
 * Returns NULL if a memory allocation fails or a lexical error is detected.
 */
t_list	*lexer(char *line)
{
	t_lexer	l;
	t_list	*tokens;
	t_list	*node;
	t_token	*content;

	tokens = NULL;
	if (!lexer_setup(&l, line))
		return (NULL);
	while (true)
	{
		content = tokenize_stream(&l);
		if (l.is_err)
			return (token_free(content), lexer_cleanup(&l, &tokens));
		if (content)
		{
			node = x_lstnew(content);
			if (!node)
				return (token_free(content), lexer_cleanup(&l, &tokens));
			ft_lstadd_back(&tokens, node);
		}
		if (l.ch == '\0')
			break ;
	}
	return (lexer_finelize(&l, &tokens));
}
