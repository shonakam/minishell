/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 00:00:38 by shonakam          #+#    #+#             */
/*   Updated: 2024/09/05 00:09:35 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	test_env(t_envlist	*envlist)
{
	printf("GETENV[USER]: [%s]\n", ft_getenv(envlist, "USER"));
	printf("CLEARNV[USER]\n");
	ft_clearenv(&envlist, "USER");
	printf("GETENV[USER]: [%s]\n", ft_getenv(envlist, "USER"));
	printf("GETENV[TEST]: [%s]\n", ft_getenv(envlist, "TEST"));
	printf("PUTENV[TEST]\n");
	ft_putenv(&envlist, "TEST", "THIS_IS_VALUE");
	printf("GETENV[TEST]: [%s]\n", ft_getenv(envlist, "TEST"));
	printf("PUTENV[TEST]\n");
	ft_putenv(&envlist, "TEST", "CHENGED_VALUE");
	printf("GETENV[TEST]: [%s]\n", ft_getenv(envlist, "TEST"));
}
