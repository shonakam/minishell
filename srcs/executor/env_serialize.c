#include "executor_internal.h"

static char	*build_string(t_list *env)
{
	t_env	*content;
	char	*s;
	char	*tmp;

	content = (t_env *)env;
	if (!content || !content->key)
		return (NULL);
	tmp = ft_strjoin(content->key, "=");
    if (!tmp)
        return (ft_dprintf(STDERR_FILENO, ERR_MALLOC), NULL);
    if (content->has_value && content->value)
    {
        s = ft_strjoin(tmp, content->value);
        return (free(tmp), ft_dprintf(STDERR_FILENO, ERR_MALLOC), NULL);
    }
    else
        s = tmp;
    return (s);
}

char	**env_serialize(t_list *env)
{
	char	**envp;
	size_t	i;
	t_list  *curr;

	envp = (char **)x_calloc(1, ft_lstsize(env) * sizeof(char *));
	if (!envp)
		return (NULL);
	i = 0;
	curr = env->next;
	while (curr)
	{
		envp[i] = build_string(env);
		if (!envp)
		{
			while (i > 0)
				free(envp[--i]);
			return (free(envp), NULL);
		}
		curr = curr->next;
		i++;
	}
	return (envp);
}
