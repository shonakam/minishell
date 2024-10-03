/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redilect_io.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 08:54:14 by shonakam          #+#    #+#             */
/*   Updated: 2024/09/21 01:43:35 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	set_bkp_fd(t_rdir *info)
{
	info->i_bkp = dup(STDIN_FILENO);
	info->o_bkp = dup(STDOUT_FILENO);
	if (info->i_bkp == -1 || info->o_bkp == -1)
	{
		perror("dup");
		exit(EXIT_FAILURE);
	}
}

void	restore_io(t_rdir *info)
{
	if (info->i_bkp != -1)
	{
		if (dup2(info->i_bkp, STDIN_FILENO) == -1)
		{
			perror("dup2");
			exit(EXIT_FAILURE);
		}
		close(info->i_bkp);
	}
	if (info->o_bkp != -1)
	{
		if (dup2(info->o_bkp, STDOUT_FILENO) == -1)
		{
			perror("dup2");
			exit(EXIT_FAILURE);
		}
		close(info->o_bkp);
	}
}
