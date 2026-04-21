#include "../ft_readline_internal.h"

static void	set_history_to_list(t_list **lst, int fd)
{
	char	*line;
	t_list	*new;

	line = get_next_line(fd);
	while (line != NULL)
	{
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		new = x_lstnew(x_strdup(line));
		if (new)
			ft_lstadd_back(lst, new);
		free(line);
		line = get_next_line(fd);
	}
}

void	ft_load_history(void)
{
	t_list	**p;
	char	*path;
	int		fd;

	p = ft_get_history();
	if (p != NULL)
		return ;
	path = get_history_path();
	fd = x_open(path, O_RDONLY, 0);
	free(path);
	if (fd != -1)
	{
		set_history_to_list(p, fd);
		close(fd);
	}
}
