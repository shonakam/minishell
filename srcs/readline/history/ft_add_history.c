#include "../ft_readline_internal.h"

static void	limit_memory_history(t_list **p)
{
	t_list	*last;

	if (!p || !*p)
		return ;
	if ((size_t)ft_lstsize(*p) > HISTSIZE)
	{
		last = ft_lstlast(*p);
		if (last->prev)
			last->prev->next = NULL;
		else
			*p = NULL;
		ft_lstdelone(last, free);
	}
}

static bool	ignore_dups(const char *line)
{
	t_list	**head;
	size_t	len;

	head = ft_get_history();
	if (!head || !*head || !(*head)->content)
		return (false);
	len = ft_strlen(line);
	if (len == ft_strlen((char *)(*head)->content) &&
		ft_strncmp((char *)(*head)->content, line, len) == 0)
	{
		return (true);
	}
	return (false);
}

void	ft_add_history(const char *line)
{
	t_list			*new;
	char			*path;
	int				fd;

	if (!line || *line == '\0' || ignore_dups(line))
		return ;
	path = get_history_path();
	fd = x_open(path, O_WRONLY | O_CREAT | O_APPEND, 0600);
	free(path);
	if (fd != -1)
	{
		ft_putendl_fd(line, fd);
		close(fd);
	}
	new = x_lstnew(x_strdup(line));
	if (!new)
		return ;
	ft_lstadd_front(ft_get_history(), new);
	limit_memory_history(ft_get_history());
}
