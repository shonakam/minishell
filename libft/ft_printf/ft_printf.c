/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosh <mosh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 03:57:16 by mosh              #+#    #+#             */
/*   Updated: 2024/04/23 23:55:55 by mosh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (*s)
	{
		len++;
		s++;
	}
	return (len);
}

size_t	ftprintf_helper(va_list ap, char format)
{
	size_t	count;

	count = 0;
	if (format == 'c')
		count += ft_putchar_fd(va_arg(ap, int), 1);
	else if (format == 's')
		count += ft_putstr_fd(va_arg(ap, char *), 1);
	else if (format == 'p')
		count += ft_putptr_fd((uintptr_t)va_arg(ap, void *), 1);
	else if (format == 'd' || format == 'i')
		count += ft_putnbr_fd(va_arg(ap, int), 1);
	else if (format == 'u')
		count += ft_put_unsigned_nbr((unsigned int)va_arg(ap, unsigned int));
	else if (format == 'x' || format == 'X')
		count += ft_puthex(va_arg(ap, int), format);
	else if (format == '%')
		count += ft_putchar_fd('%', 1);
	return (count);
}

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	va_start(ap, format);
	while (format[i] != '\0')
	{
		if (format[i] == '%')
		{
			i++;
			count += ftprintf_helper(ap, format[i]);
		}
		else
			count += ft_putchar_fd(format[i], 1);
		i++;
	}
	va_end(ap);
	return (count);
}
