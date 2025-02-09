/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rebuild_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 03:55:27 by shonakam          #+#    #+#             */
/*   Updated: 2025/02/09 04:41:52 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

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
