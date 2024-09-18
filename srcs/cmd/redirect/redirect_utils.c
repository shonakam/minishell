/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 09:09:41 by shonakam          #+#    #+#             */
/*   Updated: 2024/09/18 22:25:28 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	handle_error(const char *message)
{
	perror(message);
	exit(EXIT_FAILURE);
}

void	restore_fd(t_rdir *info)
{
	if (info->in_backup != -1) {
		if (dup2(info->in_backup, STDIN_FILENO) < 0)
			handle_error("dup2 failed to restore STDIN");
		close(info->in_backup);
	}
	if (info->out_backup != -1) {
		if (dup2(info->out_backup, STDOUT_FILENO) < 0)
			handle_error("dup2 failed to restore STDOUT");
		close(info->out_backup);
	}
}

/* toggle == 0 -> create | toggle == 1 -> free */
t_rdir	*manage_redirect(t_rdir *info, int toggle)
{
	t_rdir	*new = NULL;

	if (toggle == 0)
	{
		new = (t_rdir *)malloc(sizeof(t_rdir));
		if (!new)
		{
			perror("malloc");
			exit(EXIT_FAILURE);
		}
		new->file = NULL;
		new->mode = -1;
		new->rdir_fd = -1;
		new->in_backup = -1;
		new->out_backup = -1;
	}
	if (info && toggle == 1)
	{
		restore_fd(info);
		free(info);
	}
	return (new);
}

int	get_redirect_mode(char *arg)
{
	int	mode;

	if (ft_strcmp(arg, ">>") == 0)
		mode =  O_CREAT | O_WRONLY | O_TRUNC;
	else if (ft_strcmp(arg, ">") == 0)
		mode = O_CREAT | O_WRONLY | O_APPEND;
	else if (ft_strcmp(arg, "<") == 0)
		mode = O_RDONLY;
	else
		mode = -1;
	return (mode);
}