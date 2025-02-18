/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 14:11:36 by shonakam          #+#    #+#             */
/*   Updated: 2025/02/18 14:43:36 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	status_manager(int *status, int *backup)
{
	if (*status == 131)
		quit_message();
	if (g_signal_flag & (1 << 1))
	{
		g_signal_flag &= ~(1 << 1);
		*status = 130;
	}
	*backup = *status;
}
