/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_loop.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 19:27:57 by shonakam          #+#    #+#             */
/*   Updated: 2025/02/12 23:02:04 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static char	*read_heredoc_input(const char *delimiter)
{
	char	*line;

	g_signal_flag |= (1 << 2);
	line = readline("heredoc> ");
	g_signal_flag &= ~(1 << 2);
	if (line == NULL)
	{
		print_heredoc_error(delimiter);
		return (NULL);
	}
	return (line);
}

static int	check_delimiter(char *line, char *delimiter)
{
	return (ft_strlen(line) == ft_strlen(delimiter)) &&
		(ft_strncmp(line, delimiter, ft_strlen(line)) == 0);
}

static void	process_heredoc_line(char *line, int fd, int s, t_envlist *e)
{
	char	*processed_line;

	processed_line = expand_variables(line, s, e);
	if (processed_line == NULL)
	{
		free(line);
		return ;
	}
	ft_putendl_fd(processed_line, fd);
	free(processed_line);
}

void	*heredoc_loop(int fd, char *delimiter, int s, t_envlist *e)
{
	char	*line;

	while (1)
	{
		line = read_heredoc_input(delimiter);
		if (line == NULL)
			return (NULL);
		if (check_delimiter(line, delimiter))
		{
			free(line);
			return (NULL);
		}
		process_heredoc_line(line, fd, s, e);
		free(line);
	}
	return (NULL);
}
