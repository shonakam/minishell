/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosh <mosh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 17:15:05 by kmoshker          #+#    #+#             */
/*   Updated: 2024/04/23 19:12:46 by mosh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long	ft_atoi(const char *str)
{
	int					minus;
	unsigned long long	num;

	num = 0;
	minus = 1;
	while ((9 <= *str && *str <= 13) || *str == 32)
		str++;
	if (*str == '-')
		minus = -1;
	if (*str == '-' || *str == '+')
		str++;
	while ('0' <= *str && *str <= '9')
	{
		if (minus == 1 && (num > LONG_MAX / 10
				|| (num == LONG_MAX / 10 && 7 <= *str - '0')))
			return ((int)LONG_MAX);
		if (minus == -1 && ((num >= LONG_MAX / 10 && (8 <= *str - '0'))))
			return ((int)LONG_MIN);
		num = num * 10 + (*str - '0');
		str++;
	}
	return ((num * minus));
}

// int	ft_atoi(const char *str)
// {
// 	int					minus;
// 	unsigned long long	num;
// 	num = 0;
// 	minus = 1;
// 	while ((9 <= *str && *str <= 13) || *str == 32)
// 		str++;
// 	if (*str == '-')
// 		minus = -1;
// 	if (*str == '-' || *str == '+')
// 		str++;
// 	while ('0' <= *str && *str <= '9')
// 	{
//   		if (minus == 1 && (num > LONG_MAX / 10
// 				|| (num == LONG_MAX / 10 && 7 <= *str - '0')))
// 		{
// 			//printf("%d\n", *str - '0');
// 			return ((int)LONG_MAX);
// 		}
// 		if (minus == -1 && ((num >= LONG_MAX / 10 && (8 <= *str - '0'))))
// 			//(minus == -1 && ((num >= (unsind long long)(-LONG_MIN)
// 				//  / 10 && (8 <= *str - '0'))))
// 			return ((int)LONG_MIN);
// 		num = num * 10 + (*str - '0');
// 		//printf("%llu\n", num);
// 		str++;
// 	}
// 	//printf("ft_atoi  :  %d\n\n", (int)(num * minus));
// 	return ((int)(num * minus));
// }