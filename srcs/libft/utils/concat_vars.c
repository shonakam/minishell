/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   concat_vars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 23:56:40 by shonakam          #+#    #+#             */
/*   Updated: 2024/09/07 00:48:27 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	get_total_length(int count, ...)
{
	va_list		args;
	size_t		total_length;
	int			i;
	const char	*str;

	total_length = 0;
	i = 0;
	va_start(args, count);
	while (i < count)
	{
		str = va_arg(args, const char *);
		total_length += ft_strlen(str);
		i += 1;
	}
	va_end(args);
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
	}
	*current_position = '\0';
}

// adjustable_strjoin: 可変数の文字列を結合する
char	*concat_vars(int count, ...)
{
	va_list	args;
	char	*r;

	va_start(args, count);
	r = malloc(sizeof(char) * get_total_length(count, args) + 1);
	va_end(args);
	if (!r)
		return (NULL);
	va_start(args, count);
	concat_strings(r, count, args);
	va_end(args);
	return (r);
}
