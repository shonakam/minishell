/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 12:43:47 by shonakam          #+#    #+#             */
/*   Updated: 2024/09/18 12:46:02 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	exec_hd_support(t_command *cmd, t_minishell *m, int *p)
{
	if (cmd->next)
		handle_pipe(p, 0);
	if (handle_heredoc(cmd, &m->hd_index, m->status, m->envlist) == 1)
	{
		m->status = 0;
		if (cmd->next)
			handle_pipe(p, 1);
		return (1);
	}
	return (0);
}