/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rebuild_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 23:50:16 by shonakam          #+#    #+#             */
/*   Updated: 2024/09/16 03:45:09 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

// static char	*get_last_hd_filename(t_heredoc *hd)
// {
// 	char	*filename;

// 	while (hd)
// 	{
// 		filename = hd->filename;
// 		hd = hd->next;
// 	}
// 	return (filename);
// }

static char *get_next_hd_filename(t_heredoc **hd)
{
	char *filename = NULL;

	if (*hd)
	{
		filename = (*hd)->filename;  // 現在のヒアドキュメントのファイル名を取得
		*hd = (*hd)->next;  // リストを次に進める
	}
	return filename;
}

static int	count_hd(t_heredoc *hd)
{
	int c;

	c = 0;
	while (hd)
	{
		hd = hd->next;
		c++;
	}
	return (c);
}

int	is_here_doc_placeholder(const char *arg)
{
	if (!arg)
		return (0);
	if (ft_strcmp(arg, "<<") == 0)
		return (1);
	return (0);
}

/*
-- 
-- 
*/ 
char	**rebuild_args(t_command *cmd)
{
	char **new_argv;
	int new_argc;
	int i, j;
	int hd_count = count_hd(cmd->hd_list);
	t_heredoc *hd = cmd->hd_list;
	char *filename;

	// 新しい引数リストのサイズを計算
	new_argc = cmd->argc - (hd_count * 2) + hd_count;
	new_argv = malloc(sizeof(char *) * (new_argc + 1)); // +1 for NULL
	if (!new_argv)
		return NULL;
	// 引数リストを更新
	i = 0;
	j = 0;
	while (cmd->argv[i])
	{
		if (is_here_doc_placeholder(cmd->argv[i]))
		{
			i++;  // "<<" の次の引数（ヒアドキュメントの区切り）をスキップ
			char *filename = get_next_hd_filename(&hd);  // 次のヒアドキュメントのファイル名を取得
			if (filename)
				new_argv[j++] = ft_strdup(filename);  // ファイル名を新しい引数リストに追加
		}
		else if (cmd->argv[i] && j < new_argc) // 防止オーバーフロー
			new_argv[j++] = strdup(cmd->argv[i]);
		i++;
	}
	// printf("-- J[%d] --\n", j);
	new_argv[j] = NULL;

	// 古い引数リストを解放
	for (i = 0; i < cmd->argc; i++)
		free(cmd->argv[i]);
	free(cmd->argv);

	// 新しい引数リストを設定
	cmd->argv = new_argv;
	cmd->argc = new_argc;
	return (new_argv);
}