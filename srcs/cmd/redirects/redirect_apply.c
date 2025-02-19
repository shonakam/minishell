/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_apply.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 07:12:51 by shonakam          #+#    #+#             */
/*   Updated: 2025/02/19 23:43:54 by shonakam         ###   ########.fr       */
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

/* skips over redirection operators and their arguments */
static int	handle_redirects(char **argv, int *i, int *argc)
{
	if (!argv[*i])
		return (0);
	if (ft_strcmp(argv[*i], ">") == 0
		|| ft_strcmp(argv[*i], "<") == 0
		|| ft_strcmp(argv[*i], ">>") == 0)
	{
		if (*i + 1 < *argc)
			(*i)++;
		return (1);
	}
	return (0);
}

/* filters out redirection operators from argv. */
char	**prepare_exec_argv(char **argv, int *argc, int i, int j)
{
	char	**new_argv;

	new_argv = (char **)malloc((*argc + 1) * sizeof(char *));
	if (!new_argv)
	{
		print_syscall_error("malloc: prepare_exec_argv", ENOMEM);
		return (free_argv(argv), NULL);
	}
	while (i < *argc)
	{
		if (handle_redirects(argv, &i, argc))
		{
			i++;
			continue ;
		}
		else
			new_argv[j++] = ft_strdup(argv[i++]);
	}
	new_argv[j] = NULL;
	*argc = j;
	free_argv(argv);
	return (new_argv);
}
