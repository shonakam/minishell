/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal_conf.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 02:34:33 by shonakam          #+#    #+#             */
/*   Updated: 2025/02/13 04:48:39 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "includes/minishell.h"

// void	set_terminal_flags(int fd, int disable_signals)
// {
// 	struct termios	old_tio, new_tio;

// 	if (tcgetattr(fd, &old_tio) != 0)
// 	{
// 		print_syscall_error("tcgetattr: set_terminal_flags", 0);
// 		return ;
// 	}
// 	new_tio = old_tio;
// 	if (disable_signals)
// 		new_tio.c_lflag &= ~ISIG;
// 	if (tcsetattr(fd, TCSANOW, &new_tio) != 0)
// 	{
// 		print_syscall_error("tcsetattr: set_terminal_flags", 0);
// 		return ;
// 	}
// }

// void	reset_terminal_flags(int fd, struct termios *old_tio)
// {
// 	if (tcsetattr(fd, TCSANOW, old_tio) != 0)
// 		print_syscall_error("tcsetattr: reset_terminal_flags", 0);
// }
