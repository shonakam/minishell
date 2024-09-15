/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolve_eos_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 04:35:55 by shonakam          #+#    #+#             */
/*   Updated: 2024/09/15 02:12:27 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

char	*connect_and_free(char *s1, char *s2)
{
	char	*result;

	result = concat_vars(4, "\n", s1, "\n", s2);
	return (free(s1), result);
}
