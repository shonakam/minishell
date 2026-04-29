#include "../executor_internal.h"

static char	*get_redir_symbol(t_redir_type type)
{
	if (type == REDIR_IN)
		return (" < ");
	if (type == REDIR_OUT)
		return (" > ");
	if (type == REDIR_APPEND)
		return (" >> ");
	if (type == REDIR_HEREDOC)
		return (" << ");
	return (" ");
}

static size_t	get_total_len(t_list *args)
{
	size_t	len;
	t_list	*curr;

	len = 0;
	curr = args;
	while (curr)
	{
		len += ft_strlen(((t_arg *)curr->content)->str);
		if (curr->next)
			len++;
		curr = curr->next;
	}
	return (len);
}

static char	*append_redirs(char *res, t_list *redir_list)
{
	t_list		*curr;
	t_redirect	*redir;
	char		*tmp;
	char		*sym_file;

	curr = redir_list;
	while (curr)
	{
		redir = (t_redirect *)curr->content;
		sym_file = ft_strjoin(get_redir_symbol(redir->type), redir->target);
		if (!sym_file)
			return (ft_dprintf(STDERR_FILENO, ERR_MALLOC), NULL);
		tmp = ft_strjoin(res, sym_file);
		if (!tmp)
			return (ft_dprintf(STDERR_FILENO, ERR_MALLOC), NULL);
		free(res);
		free(sym_file);
		res = tmp;
		curr = curr->next;
	}
	return (res);
}

static char	*command_args_to_str(t_list *args)
{
	char	*res;
	t_list	*curr;
	size_t	len;

	if (!args)
		return (x_strdup(""));
	len = get_total_len(args);
	res = x_calloc(len + 1, sizeof(char));
	if (!res)
		return (NULL);
	curr = args;
	while (curr)
	{
		ft_strlcat(res, ((t_arg *)curr->content)->str, len + 1);
		if (curr->next)
			ft_strlcat(res, " ", len + 1);
		curr = curr->next;
	}
	return (res);
}

char	*ast_to_str(t_ast_node *node)
{
	char	*res;
	char	*l;
	char	*r;

	if (!node)
		return (x_strdup(""));
	if (node->type == NODE_COMMAND)
	{
		res = command_args_to_str(node->data.command->args);
		if (node->data.command->redirects)
			res = append_redirs(res, node->data.command->redirects);
		return (res);
	}
	if (node->type == NODE_PIPELINE)
	{
		l = ast_to_str(node->left);
		r = ast_to_str(node->right);
		res = join_three(l, " | ", r);
		return (free(l), free(r), res);
	}
	return (x_strdup(""));
}
