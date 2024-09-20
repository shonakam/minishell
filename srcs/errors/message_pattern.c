/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message_pattern.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 17:07:15 by shonakam          #+#    #+#             */
/*   Updated: 2024/09/20 17:11:17 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

char	*static_err_msg(int n)
{
	if (n == 1)
		return ("minishell: warning: here-document delimited by eof");
	// if (n == 2)

	// if (n == 3)
	return (NULL);
}