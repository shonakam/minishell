#include "parser_internal.h"

bool	parse_redirect_into_cmd(
	t_context *ctx, t_simple_command *cmd, t_list **tokens)
{
	t_token		*op;
	t_token		*file;
	t_redirect	*redir;

	op = token_consume(tokens);
	if (is_unexpected_at_contextual(ctx, tokens, is_word))
		return (false);
	file = token_consume(tokens);
	if (!file || file->type != TOKEN_WORD)
		return (false);
	redir = redirect_new(get_redir_type(op->type), ft_strdup(file->str));
	if (!redir)
		return (false);
	if (redir->type == REDIR_HEREDOC)
		set_heredoc_delimiter(redir, file);
	else
		redir->target = ft_strdup(file->str);
	ft_lstadd_back(&cmd->redirects, x_lstnew(redir));
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
