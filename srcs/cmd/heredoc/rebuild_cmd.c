/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rebuild_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 23:50:16 by shonakam          #+#    #+#             */
/*   Updated: 2025/02/09 11:02:45 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static void	set_cmd(t_command *cmd, int nac, char **nav)
{
	int			i;
	int			j;
	char		*filename;
	t_heredoc	*hd;

	i = 0;
	j = 0;
	hd = cmd->hd_list;
	while (cmd->argv[i])
	{
		if (is_here_doc_placeholder(cmd->argv[i]))
		{
			i++;
			filename = get_next_hd_filename(&hd);
			if (filename)
				nav[j++] = ft_strdup(filename);
		}
		else if (cmd->argv[i] && j < nac)
			nav[j++] = strdup(cmd->argv[i]);
		i++;
	}
	nav[j] = NULL;
}

char	**rebuild_args(t_command *cmd)
{
	char	**new_argv;
	int		new_argc;
	int		hd_count;

	hd_count = count_hd(cmd->hd_list);
	new_argc = cmd->argc - (hd_count * 2) + hd_count;
	new_argv = malloc(sizeof(char *) * (new_argc + 1));
	if (!new_argv)
		return (NULL);
	set_cmd(cmd, new_argc, new_argv);
	hd_count = 0;
	while (hd_count < cmd->argc)
		free(cmd->argv[hd_count++]);
	free(cmd->argv);
	cmd->argv = new_argv;
	cmd->argc = new_argc;
	return (new_argv);
}
