#include "../executor_internal.h"

static bool	should_stop_heredoc(char *line, int line_no, char *target)
{
	if (!line)
	{
		if (g_signal_flag != SIGINT)
			ft_dprintf(STDERR_FILENO, ERR_HEREDOC_EOF, line_no, target);
		return (true);
	}
	return (false);
}

static void	process_and_write_line(t_context *ctx, t_redirect *redir, int wfd, char *line)
{
	char	*expanded;

	if (redir->need_expand)
		expanded = substitute_variables(ctx, line);
	else
		expanded = x_strdup(line);
	if (expanded)
	{
		ft_putendl_fd(expanded, wfd);
		free(expanded);
	}
}

static bool heredoc_write_content(t_context *ctx, t_redirect *redir, int wfd)
{
	char	*line;
	int		line_no;
	size_t	len;

	line_no = 1;
	len = ft_strlen(redir->target);
	signal_set_mode(SIG_MODE_HEREDOC);
	while (true)
	{
		line = ft_readline(PS2);
		if (should_stop_heredoc(line, line_no, redir->target))
			break ;
		if (ft_strlen(line) == len && ft_strncmp(line, redir->target, len) == 0)
		{
			free(line);
			break ;
		}
		process_and_write_line(ctx, redir, wfd, line);
		line_no++;
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
	heredoc_write_content(ctx, redir, fd);
	close(fd);
	(*hd_index)++;
	return (true);
}

bool	heredoc_prepare_all(t_context *ctx, t_ast_node *node, int *hd_index)
{
	t_list		*curr;
	t_redirect	*redir;

	if (!node)
		return (true);
	if (node->type == NODE_COMMAND)
	{
		curr = node->data.command->redirects;
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
	}
	if (!heredoc_prepare_all(ctx, node->left, hd_index))
		return (false);
	return (heredoc_prepare_all(ctx, node->right, hd_index));
}
