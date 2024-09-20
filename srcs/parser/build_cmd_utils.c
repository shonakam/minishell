/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_cmd_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 03:42:23 by shonakam          #+#    #+#             */
/*   Updated: 2024/09/20 23:50:32 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

/*
-- 次のトークンが存在し、かつそのトークンのタイプが TOKEN_WORD であることを確認
-- 前のトークンのタイプに応じてリダイレクトを設定
-- 入力リダイレクトの場合 || 出力リダイレクトの場合
-- ファイル名が期待されているにも関わらず存在しない場合のエラーメッセージ
-- トークンのインデックスを進める
失敗時のクリーン処理必要かも?
*/
t_command	*set_argument(t_command *cmd, char *token)
{
	char	**args;

	cmd->argc += 1;
	args = malloc(sizeof(char *) * (cmd->argc + 1));
	if (!args)
		return (perror("set_argument: malloc"), NULL);
	if (cmd->argv)
	{
		cpy_args(cmd, args);
		if (!args[cmd->argc - 1])
			return (free(args), NULL);
	}
	args[cmd->argc - 1] = ft_strdup(token);
	if (!args[cmd->argc - 1])
		return (free(args), perror("set_argument: malloc arg"), NULL);
	args[cmd->argc] = NULL;
	cmd->argv = args;
	return (cmd);
}
