/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_parse.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 08:42:13 by shonakam          #+#    #+#             */
/*   Updated: 2025/02/13 09:19:32 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static int	open_file(const char *file, int f, int *rdir_fd)
{
	int		fd;

	if (*rdir_fd != -1)
		close(*rdir_fd);
	fd = open(file, f, 0644);
	if (fd == -1)
	{
		print_exec_error(file, ": No such file or directory", 1, NULL);
		*rdir_fd = INT_MIN;
		return (1);
	}
	*rdir_fd = fd;
	return (0);
}

int	parse_redirects(t_command *cmd, t_rdir *info)
{
	int		i;
	int		status;

	i = 0;
	status = 0;
	while (cmd->argv[i] && status == 0)
	{
		if (ft_strcmp(cmd->argv[i], "<") == 0 && cmd->argv[i + 1])
		{
			status = open_file(cmd->argv[i + 1], O_RDONLY, &info->rdir_i);
		}
		else if (ft_strcmp(cmd->argv[i], ">") == 0 && cmd->argv[i + 1])
		{
			status = open_file(cmd->argv[i + 1],
				O_WRONLY | O_CREAT | O_TRUNC, &info->rdir_o);
		}
		else if (ft_strcmp(cmd->argv[i], ">>") == 0 && cmd->argv[i + 1])
		{
			status = open_file(cmd->argv[i + 1],
				O_WRONLY | O_CREAT | O_APPEND, &info->rdir_o);
		}
		i++;
	}
	return (status);
}
