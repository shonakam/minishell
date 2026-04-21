#include "session_internal.h"

static int	get_next_shlvl(int current_lvl)
{
	int	next;

	next = current_lvl + 1;
	if (next < 0)
		return (0);
	if (next >= SHLVL_MAX)
	{
		ft_dprintf(STDERR_FILENO, MSG_SHLVL_WARN, next);
		return (1);
	}
	return (next);
}

static bool	set_lvl_to_env(t_list *lst, int lvl)
{
	char	*lvl_str;
	char	*line;
	bool	res;

	lvl_str = ft_itoa(lvl);
	if (!lvl_str)
		return (ft_dprintf(STDERR_FILENO, ERR_MALLOC), false);
	line = ft_strjoin(KEY_SHLVL "=", lvl_str);
	if (!line)
		return (ft_dprintf(STDERR_FILENO, ERR_MALLOC), false);
	free(lvl_str);
	res = env_set(&lst, line);
	return (free(line), res);
}

bool	update_shlvl(t_list *lst)
{
	t_env	*content;

	content = env_find(lst, KEY_SHLVL);
	if (!content || !content->value)
	{
		env_set(&lst, KEY_SHLVL "=1");
		return (true);
	}
	set_lvl_to_env(lst, get_next_shlvl(ft_atoi(content->value)));
	return (true);
}
