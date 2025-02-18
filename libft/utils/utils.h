/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 00:43:15 by shonakam          #+#    #+#             */
/*   Updated: 2025/02/09 04:23:51 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stdarg.h>

char	*concat_vars(int count, ...);
int		ft_is_numeric(char *str);
void	remove_first_arg(char **argv);
size_t	ft_strarr_size(char **strarr);

#endif