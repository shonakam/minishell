/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 20:44:04 by shonakam          #+#    #+#             */
/*   Updated: 2024/09/20 16:57:37 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SIGNAL_H
# define FT_SIGNAL_H

# include <signal.h>
extern volatile sig_atomic_t	g_signal_flag;

// void	handle_signal_main(int sig);
// void	handle_signal_heredoc(int sig);
void	handle_signal(int sig);
void	setup_signals(void);

#endif
