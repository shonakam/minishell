/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   support.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 21:39:37 by shonakam          #+#    #+#             */
/*   Updated: 2024/09/15 23:37:50 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

// エラー時にプロセスを終了
// old_fdはもう使わないので閉じる
void	redirect_fd(int old, int new)
{
	if (old != new)
	{
		if (dup2(old, new) == -1)
		{
			perror("dup2 failed");
			exit(EXIT_FAILURE);
		}
		close(old);
	}
}

int		is_executable(const char *path)
{
	if (access(path, F_OK) != 0)
		return (0);
	if (access(path, X_OK) != 0)
		return (0);
	return (1);
}

void	free_heredoc(t_command *cmd)
{
	t_heredoc	*current;
	t_heredoc	*next;

	if (cmd == NULL)
		return;
	
	current = cmd->hd_list; // `cmd` 構造体内のヒアドキュメントリストの先頭を取得
	while (current)
	{
		next = current->next;
		if (current->filename)
		{
			if (unlink(current->filename) < 0)
				perror("unlink failed");
			free(current->filename);
		}
		free(current);
		current = next;
	}
}
