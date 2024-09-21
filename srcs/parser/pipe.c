/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 22:55:59 by shonakam          #+#    #+#             */
/*   Updated: 2024/09/21 01:52:56 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

// tokenの終端がpipeなら繰り返す
t_command	*wait_pipe_cmd(t_command *head)
{
	t_command	*current;
	char		*line;

	current = head;
	while (current)
		current = current->next;
	while (1)
	{
		line = readline("pipe> ");
		if (line == NULL)
			break ;
		
		free(line);
	}
	return (head);
}
