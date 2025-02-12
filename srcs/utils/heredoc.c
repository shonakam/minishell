/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 18:23:17 by shonakam          #+#    #+#             */
/*   Updated: 2025/02/13 00:14:42 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	free_heredoc(t_command *cmd)
{
	t_heredoc	*current;
	t_heredoc	*next;

	if (!cmd)
		return ;
	current = cmd->hd_list;
	while (current)
	{
		printf("here\n");
		next = current->next;
		if (current->hd_fd != -1)
			close(current->hd_fd);
		free(current->filename);
		free(current);
		current = next;
	}
}

char	*get_next_hd_filename(t_heredoc **hd)
{
	char	*filename;

	filename = NULL;
	if (*hd)
	{
		filename = (*hd)->filename;
		*hd = (*hd)->next;
	}
	return (filename);
}

int	count_hd(t_heredoc *hd)
{
	int	c;

	c = 0;
	while (hd)
	{
		hd = hd->next;
		c++;
	}
	return (c);
}

int	is_here_doc_placeholder(const char *arg)
{
	if (!arg)
		return (0);
	if (ft_strcmp(arg, "<<") == 0)
		return (1);
	return (0);
}

int	check_delimiter(char *line, char *delimiter)
{
	return (ft_strlen(line) == ft_strlen(delimiter))
		&& (ft_strncmp(line, delimiter, ft_strlen(line)) == 0);
}
