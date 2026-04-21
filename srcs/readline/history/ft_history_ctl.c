#include "../ft_readline_internal.h"

t_list	**ft_get_history(void)
{
	static t_list	*history = NULL;

	return (&history);
}

void	ft_history_destroy(void)
{
	t_list	**hist_ptr;

	hist_ptr = ft_get_history();
	if (hist_ptr && *hist_ptr)
	{
		ft_lstclear(hist_ptr, free);
		*hist_ptr = NULL;
	}
}
