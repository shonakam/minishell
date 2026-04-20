#include "executor_internal.h"

static char	*serch_path(char *target, char *path)
{
	char	**dirs;
	char	*full_path;
	char	*tmp;
	size_t	i;

	dirs = ft_split(path, ':');
	if (!dirs)
		return (ft_dprintf(STDERR_FILENO, ERR_MALLOC), NULL);
	i = 0;
	while (dirs[i])
	{
		tmp = ft_strjoin(dirs[i], "/");
		if (!tmp)
			break ;
		full_path = ft_strjoin(tmp, target);
		free(tmp);
		if (!full_path)
			break ;
		if (access(full_path, X_OK) == 0)
			return (free_matrix(dirs), full_path);
		free(full_path);
		i++;
	}
	return (free_matrix(dirs), NULL);
}

char	*find_path(char *cmd, t_context *ctx)
{
	t_env	*node;

	if (!cmd || ft_strlen(cmd) == 0)
		return (NULL);
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, X_OK) == 0)
			return (x_strdup(cmd));
		return (NULL);
	}
	node = env_find(ctx->env_list, "PATH");
	if (!node || !node->value)
		return (NULL);
	return (serch_path(cmd, node->value));
}
