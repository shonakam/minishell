/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 20:44:04 by shonakam          #+#    #+#             */
/*   Updated: 2024/09/22 15:17:50 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SIGNAL_H
# define FT_SIGNAL_H

# include <signal.h>
extern volatile sig_atomic_t	g_signal_flag;

void	handle_signal(int sig);
void	setup_signals(void);
int		observe_signal(t_minishell *mini);

#endif
