#include "../executor_internal.h"

static bool	is_file_exists(const char *path)
{
	return (access(path, F_OK) == 0);
}

static void	append_num_to_path(char *path, int num, size_t size)
{
	char	*s;

	s = ft_itoa(num);
	if (s)
	{
		ft_strlcat(path, s, size);
		free(s);
	}
}

// "/tmp/.minish_hd_[UNIQUE_ID]"
char	*generate_hd_filename(int *hd_index)
{
	char	path[PATH_MAX];

	while (true)
	{
		ft_strlcpy(path, HEREDOC_TMP_PREFIX, PATH_MAX);
		append_num_to_path(path, *hd_index, PATH_MAX);
		if (!is_file_exists(path))
			break ;
		(*hd_index)++;
	}
	return (x_strdup(path));
}
