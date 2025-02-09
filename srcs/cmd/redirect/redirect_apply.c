/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_apply.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 07:12:51 by shonakam          #+#    #+#             */
/*   Updated: 2025/02/09 11:02:59 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	apply_redirects(t_rdir *info)
{
	if (info->rdir_i != -1)
	{
		if (dup2(info->rdir_i, STDIN_FILENO) == -1)
		{
			perror("dup2");
			exit(EXIT_FAILURE);
		}
		close(info->rdir_i);
	}
	if (info->rdir_o != -1)
	{
		if (dup2(info->rdir_o, STDOUT_FILENO) == -1)
		{
			perror("dup2");
			exit(EXIT_FAILURE);
		}
		close(info->rdir_o);
	}
}

char	**prepare_exec_argv(char **argv, int *argc)
{
	char	**new_argv;
	int		j;
	int		i;

	new_argv = malloc((*argc + 1) * sizeof(char *));
	if (!new_argv)
		handle_error("malloc");
	i = 0;
	j = 0;
	while (i < *argc)
	{
		if (ft_strcmp(argv[i], ">") == 0
			|| ft_strcmp(argv[i], "<") == 0
			|| ft_strcmp(argv[i], ">>") == 0)
		{
			if (++i < *argc)
				i++;
		}
		else
			new_argv[j++] = ft_strdup(argv[i++]);
	}
	new_argv[j] = NULL;
	free_argv(argv);
	*argc = j;
	return (new_argv);
}
