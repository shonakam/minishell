#include "parser_internal.h"

static t_redir_type	get_redir_type(t_token_type type)
{
	if (type == TOKEN_REDIRECT_IN)
		return (REDIR_IN);
	if (type == TOKEN_REDIRECT_OUT)
		return (REDIR_OUT);
	if (type == TOKEN_APPEND)
		return (REDIR_APPEND);
	return (REDIR_HEREDOC);
}

bool	is_empty_command(t_simple_command *cmd)
{
	if (!cmd->args || !((t_arg *)cmd->args->content)->str)
	{
		if (cmd->redirects)
			return (false);
		return (true);
	}
	return (false);
}

bool	parse_redirect_into_cmd(t_simple_command *cmd, t_list **tokens)
{
	t_token		*op;
	t_token		*file;
	t_redirect	*redir;

	op = token_consume(tokens);
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
	ft_lstadd_back(&cmd->redirects, ft_lstnew(redir));
	return (true);
}

bool	parse_arg_into_cmd(t_simple_command *cmd, t_list **tokens)
{
	t_token	*t;

	t = token_consume(tokens);
	if (!add_arg_to_list(&cmd->args, t))
		return (false);
	return (cmd->args != NULL);
}
