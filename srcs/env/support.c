/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   support.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 16:40:25 by shonakam          #+#    #+#             */
/*   Updated: 2024/09/04 17:24:54 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	check_null_envlist_member(t_envlist *l)
{
	int	flag;

	flag = 0;
	if (!l->key && l->value)
	{
		free(l->value);
		flag++;
	}
	else if (l->key && !l->value)
	{
		free(l->key);
		flag++;
	}
	else if (!l->key && !l->value)
		flag++;
	return (flag);
}
