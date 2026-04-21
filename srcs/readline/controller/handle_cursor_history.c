#include "../ft_readline_internal.h"

static void	history_refresh(t_readline_state *s)
{
	char	*str;

	tputs(s->caps->cr, 1, putchar_int);
	tputs(s->caps->ce, 1, putchar_int);
	if (s->hist_ptr)
		str = (char *)s->hist_ptr->content;
	else
		str = s->save_buf;
	if (!str)
		str = "";
	ft_strlcpy(s->buf, str, BUFFER_SIZE);
	s->index = ft_strlen(s->buf);
	ft_putstr_fd(s->prompt, STDOUT_FILENO);
	ft_putstr_fd(s->buf, STDOUT_FILENO);
}

static void	navigate_history(t_readline_state *s, int direction)
{
	t_list	**head;

	head = ft_get_history();
	if (s->hist_ptr == NULL && direction == K_UP)
	{
		if (!head || !*head)
			return ;
		if (s->save_buf)
			free(s->save_buf);
		s->save_buf = x_strdup(s->buf);
		s->hist_ptr = *ft_get_history();
	}
	else if (s->hist_ptr != NULL)
	{
		if (direction == K_UP && s->hist_ptr->next)
			s->hist_ptr = s->hist_ptr->next;
		else if (direction == K_DOWN)
			s->hist_ptr = s->hist_ptr->prev;
	}
}

void	ft_history_move(t_readline_state *s, int direction)
{
	navigate_history(s, direction);
	history_refresh(s);
	s->index = ft_strlen(s->buf);
}
