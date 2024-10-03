/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 08:34:03 by shonakam          #+#    #+#             */
/*   Updated: 2024/10/03 11:50:57 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_ERRORS_H
# define FT_ERRORS_H

void	handle_error(const char *message);
void	syntax_err(int n);
int		handle_exec_errors(char *path, int *p, int f);
char	*static_err_msg(int n);

#endif