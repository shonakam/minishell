#include "../executor_internal.h"

char	*append_char(char *s, char c)
{
	char	*new;
	size_t	len;

	len = 0;
	if (s)
		len = ft_strlen(s);
	new = x_calloc(len + 2, sizeof(char));
	if (!new)
		return (free(s), NULL);
	if (s)
	{
		ft_memcpy(new, s, len);
		free(s);
	}
	new[len] = c;
	new[len + 1] = '\0';
	return (new);
}

void	insert_split_words(t_list *curr, char **words)
{
	t_list	*next_backup;
	t_list	*new_node;
	size_t	i;

	free(((t_arg *)curr->content)->str);
	((t_arg *)curr->content)->str = x_strdup(words[0]);
	next_backup = curr->next;
	i = 1;
	while (words[i])
	{
		new_node = arg_node_new(words[i++]);
		curr->next = new_node;
		curr = new_node;
	}
	curr->next = next_backup;
}

bool	handle_word_splitting(t_list **curr, t_list *prev,
	t_simple_command *cmd, char *expanded)
{
	char	**words;
	t_list	*next;

	words = ft_split(expanded, ' ');
	if (!words)
		return (false);
	if (!words[0])
	{
		next = (*curr)->next;
		if (prev)
			prev->next = next;
		else
			cmd->args = next;
		ft_lstdelone(*curr, arg_free);
		*curr = next;
		free_matrix(words);
		return (true);
	}
	insert_split_words(*curr, words);
	free_matrix(words);
	return (false);
}
