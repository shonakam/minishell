/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_setup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 07:44:40 by shonakam          #+#    #+#             */
/*   Updated: 2025/02/12 23:51:56 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static char	*set_filename(const char *index)
{
	char	*base;
	char	*name;

	base = "/tmp/heredoc_temp_file_";
	name = ft_strjoin(base, index);
	if (!name)
		return (print_syscall_error("malloc: set_filename", ENOMEM), NULL);
	return (name);
}

static t_heredoc	*set_heredoc(char *del, int *index, int s, t_envlist *e)
{
	int		fd;
	char	*filename;
	char	*idx;

	fd = -1;
	while (fd < 0)
	{
		idx = ft_itoa(*index);
		filename = set_filename(idx);
		free(idx);
		fd = open(filename, O_RDWR | O_CREAT | O_TRUNC, 0644);
		if (fd < 0)
		{
			free(filename);
			(*index)++;
		}
	}
	(*index)++;
	heredoc_loop(fd, del, s, e);
	return (create_hd_node(filename, fd));
}

/* Process heredocs in commands and build a heredoc list */
void	handle_heredoc(t_command *cmd, int *index, int status, t_envlist *env)
{
	t_heredoc	*node;
	size_t		i;

	i = 0;
	while (cmd->argv && cmd->argv[i])
	{
		if (ft_strcmp(cmd->argv[i], "<<") == 0)
		{
			if (cmd->argv[i + 1])
			{
				node = set_heredoc(cmd->argv[i + 1], index, status, env);
				append_hd_node(&cmd->hd_list, node);
			}
		}
		i++;
	}
}
