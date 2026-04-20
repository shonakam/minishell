#include "../executor_internal.h"

static bool	backtrack(
	const char **p, const char **s, const char **last_p, const char **last_s)
{
	if (!*last_p)
		return (false);
	*p = *last_p + 1;
	*s = ++(*last_s);
	return (true);
}

static bool	is_match(const char *p, const char *s)
{
	const char	*last_p;
	const char	*last_s;

	last_p = NULL;
	last_s = NULL;
	while (*s)
	{
		if (*p == *s || *p == '?')
		{
			p++;
			s++;
		}
		else if (*p == '*')
		{
			last_p = p++;
			last_s = s;
		}
		else if (!backtrack(&p, &s, &last_p, &last_s))
			return (false);
	}
	while (*p == '*')
		p++;
	return (!*p);
}

static t_list	*get_matched_files(DIR *dir, char *path, char *pattern)
{
	struct dirent	*entry;
	t_list			*head;
	char			*full;

	head = NULL;
	while (true)
	{
		entry = readdir(dir);
		if (!entry)
			break ;
		if (entry->d_name[0] == '.' && pattern[0] != '.')
			continue ;
		if (is_match(pattern, entry->d_name))
		{
			if (ft_strncmp(path, "./", 2) == 0)
				full = ft_strdup(entry->d_name);
			else
				full = ft_strjoin(path, entry->d_name);
			ft_lstadd_back(&head, x_lstnew(full));
		}
	}
	return (head);
}

/*
 * NOTE: This function supports only single-level wildcard expansion.
 * (e.g., "srcs/*.c" works, but "srcs/[*]/[*.c]" is not supported).
 * To support multi-level expansion, a recursive directory traversal
 * implementation is required in the future.
 */
t_list	*scan_files(char *pattern)
{
	char	*last_slash;
	char	*path;
	char	*file_pat;
	DIR		*dir;
	t_list	*head;

	last_slash = ft_strrchr(pattern, '/');
	if (last_slash)
	{
		path = x_strndup(pattern, last_slash - pattern + 1);
		file_pat = last_slash + 1;
	}
	else
	{
		path = x_strdup("./");
		file_pat = pattern;
	}
	dir = opendir(path);
	if (!dir)
		return (free(path), NULL);
	head = get_matched_files(dir, path, file_pat);
	closedir(dir);
	free(path);
	return (head);
}
