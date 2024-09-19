/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 02:06:08 by shonakam          #+#    #+#             */
/*   Updated: 2024/09/19 08:33:50 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	handle_error(const char *message)
{
	perror(message);
	exit(EXIT_FAILURE);
}
void	print_error(const char *msg, const char *cmd)
{
	char	*s;

	s = concat_vars(6, "minishell: ", msg, " ", ":", cmd, "\n");
	write(2, s, ft_strlen(s));
	free(s);
}
