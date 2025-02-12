/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_apply.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 07:12:51 by shonakam          #+#    #+#             */
/*   Updated: 2025/02/12 21:50:52 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

t_rdir	*init_redirect(void)
{
	t_rdir	*new;

	new = malloc(sizeof(t_rdir));
	if (!new)
		return (print_syscall_error("init_redirect: malloc", ENOMEM), NULL);
	new->file = NULL;
	new->mode = -1;
	new->i_bkp = -1;
	new->o_bkp = -1;
	new->rdir_i = -1;
	new->rdir_o = -1;
	return (new);
}

void	apply_redirects(t_rdir *info)
{
	if (info->rdir_i != -1)
	{
		if (dup2(info->rdir_i, STDIN_FILENO) == -1)
		{
			print_syscall_error("dup2: apply_redirects", 0);
			exit(EXIT_FAILURE);
		}
		close(info->rdir_i);
	}
	if (info->rdir_o != -1)
	{
		if (dup2(info->rdir_o, STDOUT_FILENO) == -1)
		{
			print_syscall_error("dup2: apply_redirects", 0);
			exit(EXIT_FAILURE);
		}
		close(info->rdir_o);
	}
}

/* resize argv and and free */
/* init argc = 1 */
char	**prepare_exec_argv(char **argv, int *argc, int i, int j)
{
	char	**new_argv;

	new_argv = malloc((*argc + 1) * sizeof(char *));
	if (!new_argv)
	{
		print_syscall_error("malloc: prepare_exec_argv", ENOMEM);
		return (free_argv(argv), NULL);
	}
	while (i < *argc - 1)
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
	*argc = j;
	return (free_argv(argv), new_argv);
}
