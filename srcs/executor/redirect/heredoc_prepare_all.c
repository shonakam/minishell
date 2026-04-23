#include "../executor_internal.h"

static void	write_expanded_line(t_context *ctx, t_redirect *redir, int fd, char *line)
{
	char	*expanded;

	if (redir->need_expand)
		expanded = substitute_variables(ctx, line);
	else
		expanded = x_strdup(line);
	if (expanded)
	{
		ft_putendl_fd(expanded, fd);
		free(expanded);
	}
}

static bool	write_content(t_context *ctx, t_redirect *redir, int fd)
{
	char	*line;
	int		no;

	no = 0;
	signal_set_mode(SIG_MODE_HEREDOC);
	while (++no)
	{
		line = ft_readline(PS2);
		if (!line)
		{
			if (g_signal_flag != SIGINT)
				ft_dprintf(STDERR_FILENO, ERR_HEREDOC_EOF, no, redir->target);
			break ;
		}
		if (ft_strlen(line) == ft_strlen(redir->target)
			&& ft_strncmp(line, redir->target, ft_strlen(line)) == 0)
		{
			free(line);
			break ;
		}
		write_expanded_line(ctx, redir, fd, line);
		free(line);
	}
	signal_set_mode(SIG_MODE_IDLE);
	return (g_signal_flag != SIGINT);
}

static bool	heredoc_init(t_context *ctx, t_redirect *redir, int *hd_index)
{
	int	fd;

	redir->tmp_filename = generate_hd_filename(hd_index);
	if (!redir->tmp_filename)
		return (false);
	fd = open(redir->tmp_filename,
			O_WRONLY | O_CREAT | O_TRUNC, HEREDOC_TMP_MODE);
	if (fd == -1)
	{
		free(redir->tmp_filename);
		redir->tmp_filename = NULL;
		return (false);
	}
	write_content(ctx, redir, fd);
	close(fd);
	(*hd_index)++;
	return (true);
}

static bool	prepare_redirect_list(t_context *ctx, t_list *curr, int *hd_index)
{
	t_redirect	*redir;

	while (curr)
	{
		redir = (t_redirect *)curr->content;
		if (redir->type == REDIR_HEREDOC)
		{
			if (!heredoc_init(ctx, redir, hd_index))
				return (false);
		}
		curr = curr->next;
	}
	return (true);
}

bool	heredoc_prepare_all(t_context *ctx, t_ast_node *node, int *hd_index)
{
	if (!node)
		return (true);
	if (node->type == NODE_COMMAND)
	{
		if (!prepare_redirect_list(ctx, node->data.command->redirects, hd_index))
			return (false);
	}
	if (node->type == NODE_SUBSHELL)
	{
		if (!prepare_redirect_list(ctx, node->redirects, hd_index))
			return (false);
	}
	if (!heredoc_prepare_all(ctx, node->left, hd_index))
		return (false);
	return (heredoc_prepare_all(ctx, node->right, hd_index));
}
