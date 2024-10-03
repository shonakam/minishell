/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 00:43:15 by shonakam          #+#    #+#             */
/*   Updated: 2024/10/03 13:36:00 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_UTILS_H
# define FT_UTILS_H

#include <stdarg.h>

char	*concat_vars(int count, ...);
int		ft_is_numeric(char *str);
void	remove_first_arg(char **argv);
size_t	ft_strarr_size(char **strarr);

#endif