/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   concat_vars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 23:56:40 by shonakam          #+#    #+#             */
/*   Updated: 2024/09/12 14:44:57 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include <stdio.h>

static size_t get_total_length(int count, va_list args)
{
	size_t		total_length;
	int			i;
	const char	*str;

	total_length = 0;
	i = 0;
	while (i < count)
	{
		str = va_arg(args, const char *);
		total_length += ft_strlen(str);
		i += 1;
	}
	return (total_length);
}

static void	concat_strings(char *dest, int count, va_list args)
{
	int			i;
	const char	*str;
	char		*current_position;
	
	i = 0;
	current_position = dest;
	while (i < count)
	{
		str = va_arg(args, const char *);
		ft_memcpy(current_position, str, ft_strlen(str));
		current_position += ft_strlen(str);
		i += 1;
	}
	*current_position = '\0';
}

char	*concat_vars(int count, ...)
{
	va_list	main;
	va_list	sub;
	char	*r;

	va_start(main, count);
	va_copy(sub, main);
	r = malloc(sizeof(char) * get_total_length(count, sub) + 1);
	va_end(sub);
	if (!r)
		return (va_end(main), NULL);
	concat_strings(r, count, main);
	va_end(main);
	return (r);
}
