/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 23:06:58 by shonakam          #+#    #+#             */
/*   Updated: 2024/09/11 01:41:26 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_H
# define CMD_H

// typedef struct	s_pipe {
// 	int			left[2];
// 	int			right[2];
// }				t_pipe;

typedef struct	s_pipe {
	int	read_end;
	int	write_end;
}				t_pipe;


#endif
