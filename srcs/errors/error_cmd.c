/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 02:06:08 by shonakam          #+#    #+#             */
/*   Updated: 2024/09/20 10:14:43 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	handle_error(const char *message)
{
	perror(message);
	exit(EXIT_FAILURE);
}

void	print_error(const char *msg, const char *cmd)
{
	char	*s;

	s = concat_vars(6, "minishell: ", msg, " ", ":", cmd, "\n");
	write(2, s, ft_strlen(s));
	free(s);
}

static	int	is_directory(char *path, int *p)
{
	struct stat sb;

	if (stat(path, &sb) == -1)
	{
		return (ft_putstr_fd("minishell: no such file or directory: ",
				STDERR_FILENO), ft_putendl_fd(path, STDERR_FILENO), 127);
	}
	if (S_ISDIR(sb.st_mode))
	{
		if (p && p[WRITE] != -1)
			return (exit(EXIT_FAILURE), handle_pipe(p, 1), 1);
		if (!ft_strchr(path, '/'))
		{	
			ft_putstr_fd("minishell: ", STDERR_FILENO);
			ft_putstr_fd(path, STDERR_FILENO);
			ft_putendl_fd(": Is a directory", STDERR_FILENO); 
			return (126);
		}
	}
	return (0);
}

int	handle_exec_errors(char *path, int *p)
{
	int	status;

	status = 0;
	// if (status > 0)
	// 	return (status);
	if (access(path, F_OK) && access(path, X_OK) == -1)
	{
		if (p && p[WRITE] != -1)
			return (exit(EXIT_FAILURE), handle_pipe(p, 1), 1);
		ft_putstr_fd("minishell: permission denied: ", STDERR_FILENO);
		return (ft_putendl_fd(path, STDERR_FILENO), 126);
	}
	if (access(path, F_OK) == -1)
	{
		if (p && p[WRITE] != -1)
			return (exit(EXIT_FAILURE), handle_pipe(p, 1), 1);
		ft_putstr_fd("minishell: command not found: ", STDERR_FILENO);
		return (ft_putendl_fd(path, STDERR_FILENO), 127);
	}
	status = is_directory(path, p);
	return (status);
}
