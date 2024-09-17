/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 02:06:08 by shonakam          #+#    #+#             */
/*   Updated: 2024/09/17 01:04:33 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	print_error(const char *msg, const char *cmd)
{
	char	*s;

	s = concat_vars(6, "minishell: ", msg, " ", ":", cmd, "\n");
	write(2, s, ft_strlen(s));
	free(s);
}
