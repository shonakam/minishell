/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_bin_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 04:02:52 by shonakam          #+#    #+#             */
/*   Updated: 2025/02/13 21:06:30 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static char	*concat_path(const char *dir, const char *cmd)
{
	size_t	len_dir;
	size_t	len_cmd;
	char	*full_path;

	len_dir = ft_strlen(dir);
	len_cmd = ft_strlen(cmd);
	full_path = malloc(len_dir + len_cmd + 2);
	if (!full_path)
		return (print_syscall_error("malloc: concat_path", ENOMEM), NULL);
	ft_strcpy(full_path, dir);
	ft_strcat(full_path, "/");
	ft_strcat(full_path, cmd);
	return (full_path);
}

static char	*find_executable_path(char **paths, char *cmd)
{
	char	*path;
	char	*r;
	int		i;

	i = 0;
	r = NULL;
	while (paths[i])
	{
		path = concat_path(paths[i++], cmd);
		if (is_executable(path))
		{
			r = ft_strdup(path);
			free(path);
			break ;
		}
		free(path);
	}
	return (r);
}

/*  unset $PATH == */
char	*get_bin_path(t_envlist *list, char *cmd)
{
	char	**paths;
	char	*path;

	paths = ft_split(ft_getenv(list, "PATH"), ':');
	if (!paths)
	{
		path = ft_strdup(cmd);
		if (!path)
			return (print_syscall_error("malloc: get_bin_path",
					ENOMEM), NULL);
		return (path);
	}
	path = find_executable_path(paths, cmd);
	free_split(paths);
	if (!path)
	{
		path = ft_strdup(cmd);
		if (!path)
			return (print_syscall_error("malloc: get_bin_path",
					ENOMEM), NULL);
		return (path);
	}
	return (path);
}
