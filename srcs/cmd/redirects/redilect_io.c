/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redilect_io.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 08:54:14 by shonakam          #+#    #+#             */
/*   Updated: 2025/02/18 14:47:35 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	set_backup_fd(t_rdir *info)
{
	info->i_bkp = dup(STDIN_FILENO);
	if (info->i_bkp == -1)
	{
		print_syscall_error("dup(STDIN_FILENO): set_backup_fd", 0);
		exit(EXIT_FAILURE);
	}
	info->o_bkp = dup(STDOUT_FILENO);
	if (info->o_bkp == -1)
	{
		print_syscall_error("dup(STDOUT_FILENO): set_backup_fd", 0);
		close(info->i_bkp);
		info->i_bkp = -1;
		exit(EXIT_FAILURE);
	}
}

void	restore_backup_io(t_rdir *info)
{
	if (info->i_bkp != -1)
	{
		if (dup2(info->i_bkp, STDIN_FILENO) == -1)
		{
			print_syscall_error("dup2(STDIN): restore_backup_io", 0);
		}
		close(info->i_bkp);
		info->i_bkp = -1;
	}
	if (info->o_bkp != -1)
	{
		if (dup2(info->o_bkp, STDOUT_FILENO) == -1)
		{
			print_syscall_error("dup2(STDOUT): restore_backup_io", 0);
		}
		close(info->o_bkp);
		info->o_bkp = -1;
	}
}
