/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosh <mosh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 22:40:53 by kmoshker          #+#    #+#             */
/*   Updated: 2024/04/23 23:54:31 by mosh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	ft_putptr_fd(uintptr_t ptr, int fd)
{
	char	*hex_digits;
	char	buffer[20];
	size_t	i;
	size_t	count;

	hex_digits = "0123456789abcdef";
	i = 0;
	count = 0;
	if (!ptr)
	{
		count += ft_putstr_fd("0x0", fd);
		return (count);
	}
	while (ptr)
	{
		buffer[i++] = hex_digits[ptr % 16];
		ptr /= 16;
	}
	count += ft_putstr_fd("0x", fd);
	while (i--)
		count += ft_putchar_fd(buffer[i], fd);
	return (count);
}

size_t	ft_puthex(unsigned int num, char format)
{
	char	*hex_digits;
	char	buff[10];
	size_t	i;
	size_t	count;

	if (format == 'x')
		hex_digits = "0123456789abcdef";
	else if (format == 'X')
		hex_digits = "0123456789ABCDEF";
	i = 0;
	count = 0;
	if (num == 0)
		return (ft_putchar_fd('0', 1));
	while (num)
	{
		buff[i++] = hex_digits[num % 16];
		num /= 16;
	}
	while (i--)
		count += ft_putchar_fd(buff[i], 1);
	return (count);
}

size_t	ft_put_unsigned_nbr(unsigned int n)
{
	size_t	count;

	count = 0;
	if (n == 0)
		return (ft_putchar_fd('0', 1));
	if (n >= 10)
	{
		count += ft_put_unsigned_nbr(n / 10);
	}
	count += ft_putchar_fd(n % 10 + '0', 1);
	return (count);
}
