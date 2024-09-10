/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosh <mosh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 11:15:51 by mosh              #+#    #+#             */
/*   Updated: 2024/04/23 23:51:16 by mosh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdint.h>
# include <stdlib.h>
# include <stddef.h>
# include <unistd.h>
# include <limits.h>
# include "../libft.h"

size_t	ft_putchar_fd(int c, int fd);
size_t	ft_putstr_fd(char *str, int fd);
size_t	ft_putptr_fd(uintptr_t ptr, int fd);
size_t	ft_puthex(unsigned int num, char format);
size_t	ft_put_unsigned_nbr(unsigned int n);
size_t	ft_putnbr_fd(int n, int fd);
size_t	ftprintf_helper(va_list ap, char format);
int		ft_printf(const char *format, ...)
		__attribute__((format(printf, 1, 2)));
#endif