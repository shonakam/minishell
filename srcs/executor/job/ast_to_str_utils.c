#include "../executor_internal.h"

char	*get_redir_symbol(t_redir_type type)
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

size_t	get_total_len(t_list *args)
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

