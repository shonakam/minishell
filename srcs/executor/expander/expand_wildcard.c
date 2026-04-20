#include "../executor_internal.h"

static bool	is_wildcard_target(const char *arg)
{
	return (arg && ft_strchr(arg, '*'));
}

void	lstsort(t_list *lst, size_t n)
{
	t_list	*cur;
	void	*tmp;
	bool	swapped;

	if (!lst)
		return ;
	swapped = true;
	while (swapped)
	{
		swapped = false;
		cur = lst;
		while (cur && cur->next)
		{
			if (cur->content && cur->next->content &&
				ft_strncmp(cur->content, cur->next->content, n) > 0)
			{
				tmp = cur->content;
				cur->content = cur->next->content;
				cur->next->content = tmp;
				swapped = true;
			}
			cur = cur->next;
		}
	}
}

static t_list	*expand_single_arg(char *str)
{
	t_list	*raw;
	t_list	*curr;
	t_list	*new_list;
	t_list	*tmp;

	if (is_wildcard_target(str))
	{
		raw = scan_files(str);
		if (raw)
		{
			new_list = NULL;
			curr = raw;
			while (curr)
			{
				tmp = arg_node_new((char *)curr->content);
				if (!tmp)
					return (NULL);
				ft_lstadd_back(&new_list, tmp);
				curr = curr->next;
			}
			ft_lstclear(&raw, free);
			return (new_list);
		}
	}
	return (arg_node_new(str));
}

/*
* Wildcard Expansion Steps:
* 1. Identify: Scan argv for arguments containing the '*' wildcard.
* 2. Collect: Open the current directory and gather all matching filenames.
* (Note: Skip files starting with '.' unless explicitly requested).
* 3. Sort: Sort the collected filenames alphabetically to match Bash behavior.
* 4. Rebuild: Create a new argv array by:
* - Keeping non-wildcard arguments.
* - Expanding the '*' into multiple filename arguments.
* 5. Clean: Free the old argv and the temporary filename list.
*/
bool	expand_wildcard(t_simple_command *cmd)
{
	t_list	*curr;
	t_list	*new_args_list;
	t_list	*expanded_nodes;

	if (!cmd || !cmd->args)
		return (true);
	new_args_list = NULL;
	curr = cmd->args;
	while (curr)
	{
		expanded_nodes = expand_single_arg(((t_arg *)curr->content)->str);
		if (!new_args_list)
			new_args_list = expanded_nodes;
		else
			ft_lstlast(new_args_list)->next = expanded_nodes;
		curr = curr->next;
	}
	ft_lstclear(&cmd->args, (void (*)(void *))arg_free);
	cmd->args = new_args_list;
	return (true);
}
