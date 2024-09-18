/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 07:12:51 by shonakam          #+#    #+#             */
/*   Updated: 2024/09/18 22:42:21 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

char	**prepare_exec_argv(char **argv, int argc)
{
	char	**new_argv;
	int 	j;
	int		i;

	new_argv = malloc((argc + 1) * sizeof(char *));
	if (!new_argv)
		handle_error("malloc");
	i = 0;
	j = 0;
	while (i < argc)
	{
		if (ft_strcmp(argv[i], ">") == 0
			|| ft_strcmp(argv[i], "<") == 0
			|| ft_strcmp(argv[i], ">>") == 0)
		{
			if (++i < argc) // ファイル名が存在する場合のみ
				i++;
		}
		else
			new_argv[j++] = ft_strdup(argv[i++]);
	}
	new_argv[j] = NULL;
	free_argv(argv);
	return (new_argv);
}

void	validate_file(t_rdir *info)
{
	if (0 < info->rdir_fd)
		close (info->rdir_fd);
	if (info->mode == O_RDONLY && info->file)
	{
		info->rdir_fd = open(info->file, O_RDONLY);
		if (info->rdir_fd  < 0)
			handle_error("No such file or directory");
	}
	else if (info->mode == (O_CREAT | O_WRONLY | O_TRUNC) && info->file)
	{
		info->rdir_fd = open(info->file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	}
	else if (info->mode == (O_CREAT | O_WRONLY | O_APPEND) && info->file)
	{
		info->rdir_fd = open(info->file, O_CREAT | O_WRONLY | O_APPEND, 0644);
	}
}

void	set_backup_fd(t_rdir *info)
{
	info->in_backup = dup(STDIN_FILENO);
	info->out_backup = dup(STDOUT_FILENO);
	if (info->mode == O_RDONLY)
	{
		if (dup2(info->rdir_fd, STDIN_FILENO) < 0)
			handle_error("dup2 failed for input redirection");
	} 
	else if (info->mode == (O_CREAT | O_WRONLY | O_TRUNC)
			 || info->mode == (O_CREAT | O_WRONLY | O_APPEND))
	{
		if (dup2(info->rdir_fd, STDOUT_FILENO) < 0)
			handle_error("dup2 failed for output redirection");
	}
	close(info->rdir_fd);
}

/*
-- 複数のリダイレクションが存在する場合, IN/OUTともに最後のものが有効
-- 解析 -> 予約語とファイルパスの検証 -> 最後を参照
-- [<]でファイルがない場合エラ- [>> >] syntax err
-- 
*/
t_rdir	*handle_redirection(t_command *cmd)
{
	t_rdir	*info;
	int		i;

	info = manage_redirect(NULL, 0);
	i = 1;
	while (i < cmd->argc)
	{
		info->mode = get_redirect_mode(cmd->argv[i]);
		if (info->mode != -1)
		{
			if (i + 1 < cmd->argc)
			{
				info->file = cmd->argv[i + 1];
				validate_file(info);
				i++;
			}
		}
		i++;
	}
	cmd-> argv = prepare_exec_argv(cmd->argv, cmd->argc);
	set_backup_fd(info);
	return (info);
}
