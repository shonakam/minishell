#include "../executor_internal.h"

static char	*unquote_str(char *str)
{
	char	*res;
	size_t	i;
	size_t	j;
	char	q;

	if (!str)
		return (NULL);
	res = x_calloc(ft_strlen(str) + 1, sizeof(char));
	i = 0;
	j = 0;
	q = 0;
	while (str[i])
	{
		if (!q && (str[i] == '\'' || str[i] == '\"'))
			q = str[i++];
		else if (q && str[i] == q)
		{
			q = 0;
			i++;
		}
		else
			res[j++] = str[i++];
	}
	return (res);
}

bool	remove_quotes(t_simple_command *cmd)
{
	t_list	*curr;
	t_arg	*arg;
	char	*cleaned;

	curr = cmd->args;
	while (curr)
	{
		arg = (t_arg *)curr->content;
		cleaned = unquote_str(arg->str);
		if (!cleaned)
			return (false);
		free(arg->str);
		arg->str = cleaned;
		arg->state = TOKEN_NONE;
		curr = curr->next;
	}
	return (true);
}