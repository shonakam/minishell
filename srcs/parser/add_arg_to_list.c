#include "parser_internal.h"

bool	add_arg_to_list(t_list **args_head, t_token *token)
{
	t_arg	*new_arg;
	t_list	*new_node;

	new_arg = x_calloc(1, sizeof(t_arg));
	if (!token)
		return (false);
	new_arg->str = x_strdup(token->str);
	if (!new_arg->str)
		return (false);
	new_arg->state = token->state;
	new_node = ft_lstnew(new_arg);
	if (!new_node)
		return (free(new_arg->str), free(new_arg), false);
	ft_lstadd_back(args_head, new_node);
	return (true);
}
