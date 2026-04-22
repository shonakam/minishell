#include "../parser_internal.h"

t_arg	*arg_new(char *str, t_qstate state)
{
	t_arg	*arg;

	arg = (t_arg *)x_calloc(1, sizeof(t_arg));
	if (!arg)
		return (NULL);
	arg->str = x_strdup(str);
	if (!arg->str)
		return (free(arg), NULL);
	arg->state = state;
	return (arg);
}

void	arg_free(void *content)
{
	t_arg	*arg;

	if (!content)
		return ;
	arg = (t_arg *)content;
	if (arg->str)
		free(arg->str);
	free(arg);
}

bool	arg_append(t_list **args_head, t_token *token)
{
	t_arg	*new_arg;
	t_list	*new_node;

	if (!token)
		return (false);
	new_arg = arg_new(token->str, token->state);
	if (!new_arg)
		return (false);
	new_node = x_lstnew(new_arg);
	if (!new_node)
		return (arg_free(new_arg), false);
	ft_lstadd_back(args_head, new_node);
	return (true);
}

bool	arg_is_empty(t_arg *arg)
{
	if (!arg)
		return (true);
	if (!arg->str || !arg->str[0])
		return (true);
	return (false);
}
