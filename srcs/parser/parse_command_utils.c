#include "parser_internal.h"

/*
 * Parse a redirection operator and its target filename.
 */
static t_redirect	*parse_redirect(t_context *ctx, t_list **tokens)
{
	t_token		*op;
	t_token		*file;
	t_redirect	*redir;

	op = token_consume(tokens);
	if (is_unexpected_at_contextual(ctx, tokens, is_word))
		return (NULL);
	file = token_consume(tokens);
	redir = redirect_new(get_redir_type(op->type), file->str);
	if (!redir)
		return (NULL);
	if (redir->type == REDIR_HEREDOC)
		set_heredoc_delimiter(redir, file);
	return (redir);
}

/* Simple Command (ls > file) */
bool	parse_redirect_into_cmd(
	t_context *ctx, t_simple_command *cmd, t_list **tokens)
{
	t_redirect	*redir;

	redir = parse_redirect(ctx, tokens);
	if (!redir)
		return (false);
	ft_lstadd_back(&cmd->redirects, x_lstnew(redir));
	return (true);
}

/* Subshell ((ls) > file) */
bool	parse_redirect_into_node(
	t_context *ctx, t_ast_node *node, t_list **tokens)
{
	t_redirect	*redir;
	t_list		*new_node;

	redir = parse_redirect(ctx, tokens);
	if (!redir)
		return (false);
	new_node = x_lstnew(redir);
	if (!new_node)
		return (redirect_free(redir), false);
	ft_lstadd_back(&node->redirects, new_node);
	return (true);
}

bool	parse_arg_into_cmd(t_simple_command *cmd, t_list **tokens)
{
	t_token	*t;

	t = token_consume(tokens);
	if (!arg_append(&cmd->args, t))
		return (false);
	return (cmd->args != NULL);
}
