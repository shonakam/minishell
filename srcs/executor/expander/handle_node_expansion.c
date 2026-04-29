#include "../executor_internal.h"

static void	advance_pointers(t_list **curr, t_list **prev)
{
	if (curr == NULL || *curr == NULL)
		return;
	*prev = *curr;
	*curr = (*curr)->next;
}

static bool	apply_result_to_list(t_list **curr, t_list *prev,
	t_simple_command *cmd, char *exp)
{
	t_arg	*arg;

	arg = (t_arg *)(*curr)->content;
	if (arg->state == TOKEN_NONE && exp)
	{
		if (handle_word_splitting(curr, prev, cmd, exp))
			return (true);
	}
	if (exp)
	{
		free(arg->str);
		arg->str = x_strdup(exp);
	}
	return (false);
}

bool	handle_node_expansion(t_context *ctx, t_simple_command *cmd,
	t_list **curr, t_list **prev)
{
	t_arg	*arg;
	char	*exp;

	arg = (t_arg *)(*curr)->content;
	if (arg->state == TOKEN_IN_SINGLE)
	{
		advance_pointers(curr, prev);
		return (true);
	}
	exp = substitute_variables(ctx, arg->str);
	if (!exp)
		return (false);
	if (apply_result_to_list(curr, *prev, cmd, exp))
	{
		free(exp);
		advance_pointers(curr, prev);
		return (true);
	}
	free(exp);
	advance_pointers(curr, prev);
	return (true);
}
