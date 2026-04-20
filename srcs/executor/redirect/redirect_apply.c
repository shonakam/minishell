#include "../executor_internal.h"

static int	get_default_fd(t_redir_type type)
{
	if (type == REDIR_IN || type == REDIR_HEREDOC)
		return (STDIN_FILENO);
	return (STDOUT_FILENO);
}

static bool	open_and_dup2(
	char *path, int flags, int target_fd, bool should_unlink)
{
	int	fd;

	fd = x_open(path, flags, 0644);
	if (fd == -1)
		return (false);
	if (should_unlink)
        unlink(path);
	if (x_dup2(fd, target_fd) < 0)
		return (close(fd), false);
	return (close(fd), true);
}

static bool	apply_single_redirect(t_redirect *redir)
{
	int	target_fd;

	if (redir->fd != -1)
		target_fd = redir->fd;
	else
		target_fd = get_default_fd(redir->type);
	if (redir->type == REDIR_IN)
		return (open_and_dup2(redir->target, O_RDONLY, target_fd, false));
	if (redir->type == REDIR_OUT)
		return (open_and_dup2(
			redir->target, O_WRONLY | O_CREAT | O_TRUNC, target_fd, false));
	if (redir->type == REDIR_APPEND)
		return (open_and_dup2(
			redir->target, O_WRONLY | O_CREAT | O_APPEND, target_fd, false));
	if (redir->type == REDIR_HEREDOC)
		return (open_and_dup2(redir->tmp_filename, O_RDONLY, target_fd, true));
	return (true);
}

bool	redirect_apply(t_list *redirects)
{
	while (redirects)
	{
		if (!apply_single_redirect(redirects->content))
		{
			return (false);
		}
		redirects = redirects->next;
	}
	return (true);
}
