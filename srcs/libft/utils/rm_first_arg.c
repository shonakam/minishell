/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rm_first_arg.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 00:39:05 by shonakam          #+#    #+#             */
/*   Updated: 2024/09/07 00:44:27 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	remove_first_arg(char **argv)
{
	char	**current;

	if (argv == NULL || *argv == NULL)
		return;

	free(*argv);
	current = argv;
	while (*current)
	{
		*current = *(current + 1);
		current++;
	}
	*current = NULL;
}
