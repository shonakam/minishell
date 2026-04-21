#include "../ft_readline_internal.h"

static void	move_cursor_physically(
	t_readline_state *s, size_t old_idx, size_t new_idx)
{
	size_t	i;

	if (new_idx > old_idx)
	{
		i = 0;
		while (i++ < (new_idx - old_idx))
			tputs(s->caps->nd, 1, putchar_int);
	}
	else if (new_idx < old_idx)
	{
		i = 0;
		while (i++ < (old_idx - new_idx))
			tputs(s->caps->le, 1, putchar_int);
	}
}

static void	action_cursor_move(t_readline_state *s, int direction)
{
	size_t	old_idx;

	old_idx = s->index;
	if (direction == K_LEFT && s->index > 0)
		s->index--;
	else if (direction == K_RIGHT && s->buf[s->index] != '\0')
		s->index++;
	if (old_idx != s->index)
		move_cursor_physically(s, old_idx, s->index);
}

static void	action_cursor_jump(t_readline_state *s, int target_type)
{
	size_t	old_idx;
	size_t	new_idx;

	old_idx = s->index;
	if (target_type == K_HOME)
		new_idx = 0;
	else
		new_idx = ft_strlen(s->buf);
	if (old_idx != new_idx)
	{
		move_cursor_physically(s, old_idx, new_idx);
		s->index = new_idx;
	}
}

static void	action_word_move(t_readline_state *s, int direction)
{
	size_t	old_idx;
	size_t	new_idx;

	old_idx = s->index;
	new_idx = old_idx;
	if (direction == K_LEFT)
	{
		while (new_idx > 0 && s->buf[new_idx - 1] == ' ')
			new_idx--;
		while (new_idx > 0 && s->buf[new_idx - 1] != ' ')
			new_idx--;
	}
	else
	{
		while (s->buf[new_idx] != '\0' && s->buf[new_idx] != ' ')
			new_idx++;
		while (s->buf[new_idx] != '\0' && s->buf[new_idx] == ' ')
			new_idx++;
	}
	if (old_idx != new_idx)
	{
		move_cursor_physically(s, old_idx, new_idx);
		s->index = new_idx;
	}
}

int	handle_cursor(t_readline_state *s, int index)
{
	char	*seq;

	seq = &s->in[index];
	if (seq[1] == '[')
	{
		if (seq[2] == KC_UP)
			ft_history_move(s, K_UP);
		else if (seq[2] == KC_DOWN)
			ft_history_move(s, K_DOWN);
		else if (seq[2] == KC_LEFT)
			action_cursor_move(s, K_LEFT);
		else if (seq[2] == KC_RIGHT)
			action_cursor_move(s, K_RIGHT);
		else if (seq[2] == KC_HOME)
			action_cursor_jump(s, K_HOME);
		else if (seq[2] == KC_END)
			action_cursor_jump(s, K_END);
		if (seq[2] == '1' && ft_strncmp(seq + 1, SEQ_CTRL_LEFT, 5) == 0)
			return (action_word_move(s, K_LEFT), 6);
		else if (seq[2] == '1' && ft_strncmp(seq + 1, SEQ_CTRL_RIGHT, 5) == 0)
			return (action_word_move(s, K_RIGHT), 6);
		return (3);
	}
	return (1);
}
