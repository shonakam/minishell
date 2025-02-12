/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_node.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 18:34:28 by shonakam          #+#    #+#             */
/*   Updated: 2025/02/12 23:05:08 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

t_heredoc	*create_hd_node(char *filename, int fd)
{
	t_heredoc	*new_node;

	new_node = (t_heredoc *)malloc(sizeof(t_heredoc));
	if (new_node == NULL)
		return (print_syscall_error("malloc: create_hd_node", ENOMEM), NULL);
	new_node->filename = strdup(filename);
	if (new_node->filename == NULL)
	{
		print_syscall_error("create_hd_node: ft_strdup", ENOMEM);
		return (free(new_node), NULL);
	}
	new_node->hd_fd = fd;
	new_node->filename = filename;
	new_node->prev = NULL;
	new_node->next = NULL;
	return (new_node);
}

void	append_hd_node(t_heredoc **head, t_heredoc *new_node)
{
	t_heredoc	*last;

	last = *head;
	if (*head == NULL)
	{
		*head = new_node;
		return ;
	}
	while (last->next != NULL)
		last = last->next;
	last->next = new_node;
	new_node->prev = last;
}
