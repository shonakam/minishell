#include "parser_internal.h"

/**
 * Skip trailing newline tokens.
 * In shell grammar, multiple newlines after a command list are ignored.
 */
static void	skip_trailing_newlines(t_list **tokens)
{
	t_token	*token;

	while (*tokens)
	{
		token = (*tokens)->content;
		if (token->type != TOKEN_NEWLINE)
			break ;
		*tokens = (*tokens)->next;
	}
}

/*
 * Parses the list of tokens into an Abstract Syntax Tree (AST).
 *
 * This parser implements a recursive descent algorithm that:
 * 1. Follows shell grammar precedence (List -> Pipeline -> Command).
 * 2. Handles recursive structures such as subshells, which may contain
 * nested lists of commands.
 * 3. Advances the token list pointer as tokens are successfully consumed.
 * 4. Builds a tree structure where internal nodes represent operators
 * (e.g., |, &&, ||) and leaf nodes represent simple commands or subshells.
 *
 * Returns a pointer to the root of the AST, or NULL if a syntax error
 * is encountered or memory allocation fails.
 */
t_ast_node	*parser(t_context *ctx, t_list **tokens)
{
	t_ast_node	*ast;

	ctx->is_err_detected = false;
	if (!tokens || !*tokens)
		return (NULL);
	if (is_unexpected_at_start(ctx, tokens))
		return (NULL);
	ast = parse_list(ctx, tokens);
	if (!ast)
		return (NULL);
	skip_trailing_newlines(tokens);
	if (is_unexpected_at_end(ctx, tokens))
		return (ast_node_free(ast), NULL);
	return (ast);
}
