/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_loop.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 19:27:57 by shonakam          #+#    #+#             */
/*   Updated: 2025/02/18 14:09:31 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static char	*read_heredoc_input(const char *delimiter)
{
	char	*line;

	rl_event_hook = handle_heredoc_signal;
	g_signal_flag |= (1 << 3);
	line = readline("heredoc> ");
	if (observe_sigint(line, 7))
	{
		g_signal_flag &= ~(1 << 3);
		return (NULL);
	}
	g_signal_flag &= ~(1 << 3);
	if (line == NULL)
	{
		print_heredoc_error(delimiter);
		return (NULL);
	}
	return (line);
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

static char	*remove_delimiter_quotes(const char *str, int *have_quote)
{
	size_t	len;
	size_t	i;
	size_t	j;
	char	*result;

	len = strlen(str);
	result = malloc(len + 1);
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	*have_quote = 0;
	while (i < len)
	{
		if ((str[i] == '"' || str[i] == '\''))
		{
			i++;
			*have_quote = 1;
			continue ;
		}
		result[j++] = str[i++];
	}
	result[j] = '\0';
	return (result);
}

void	*heredoc_loop(int fd, char *delimiter, int s, t_envlist *e)
{
	char	*line;
	char	*del;
	int		have_quote;

	del = remove_delimiter_quotes(delimiter, &have_quote);
	if (!del)
		return (print_syscall_error("malloc: heredoc_loop", ENOMEM), NULL);
	while (1)
	{
		line = read_heredoc_input(del);
		if (line == NULL)
			return (free(del), NULL);
		if (check_delimiter(line, del))
			return (free(line), free(del), NULL);
		if (have_quote == 0)
			process_heredoc_line(line, fd, s, e);
		else
			ft_putendl_fd(line, fd);
		free(line);
	}
	return (free(del), NULL);
}
