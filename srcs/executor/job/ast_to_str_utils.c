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

char	*join_three(char *s1, char *s2, char *s3)
{
	char	*tmp;
	char	*res;

	tmp = ft_strjoin(s1, s2);
	if (!tmp)
		return (ft_dprintf(STDERR_FILENO, ERR_MALLOC), NULL);
	res = ft_strjoin(tmp, s3);
	if (!res)
		return (ft_dprintf(STDERR_FILENO, ERR_MALLOC), free(tmp), NULL);
	return (free(tmp), res);
}

