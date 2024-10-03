/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strarr_size.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 13:34:39 by shonakam          #+#    #+#             */
/*   Updated: 2024/10/03 13:35:41 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

size_t	ft_strarr_size(char **strarr)
{
	size_t	count;
	
	count = 0;
	if (!strarr)
		return (0);
	while (strarr[count])
		count++;
	return (count);
}
