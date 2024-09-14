/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 21:57:16 by shonakam          #+#    #+#             */
/*   Updated: 2024/09/14 23:53:38 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static int	is_valid_identifier(const char *str)
{
	if (!str || !*str)
		return (1);
	if (!ft_isalpha(*str) && *str != '_')
		return (1);
	while (*str)
	{
		if (!ft_isalnum(*str) && *str != '_')
			return (1);
		str++;
	}
	return (0);
}

int	cmd_unset(t_command *cmd, t_envlist *envlist)
{
	char	*s;

	if (!cmd->argv[1])
		return (0);	
	if (is_valid_identifier(cmd->argv[1]))
	{
		s = concat_vars(3, "minishell: unset: `",
			cmd->argv[1], "': not a valid identifier\n");
		ft_putstr_fd(s, STDERR_FILENO);
		free(s);
		return (1);
	}
	ft_clearenv(&envlist, cmd->argv[1]);
	return (0);
}
