/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_cmd_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 03:42:23 by shonakam          #+#    #+#             */
/*   Updated: 2024/09/12 18:22:59 by shonakam         ###   ########.fr       */
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
// void	handle_io_redirect(t_command *cmd, t_token **tokens, int *i)
// {
	// if (tokens[++(*i)] && tokens[*i]->type == TOKEN_WORD)
	// {
	// 	if (tokens[*i - 1]->type == METACHAR_INPUT_REDIRECT)
	// 	{
	// 		cmd->input_fd = open(tokens[*i]->word, O_RDONLY);
	// 		if (cmd->input_fd < 0)
	// 			perror("handle_io_redirect: open input file");
	// 	}
	// 	else if (tokens[*i - 1]->type == METACHAR_OUTPUT_REDIRECT)
	// 	{
	// 		cmd->output_fd = open(tokens[*i]->word, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	// 		if (cmd->output_fd < 0)
	// 			perror("handle_io_redirect: open output file");
	// 	}
	// }
	// else
	// 	perror("handle_io_redirect: expected file name");
	// (*i)++;
// }

/*
-- APPENDの次のトークンがファイル名であることを確認
-- ファイルをオープンしてファイルディスクリプタを取得
-- append_fd にファイルディスクリプタを設定
*/
// void	handle_append(t_command *cmd, t_token **tokens, int *i)
// {
// 	char	*file;
// 	int		fd;

// 	if (tokens[*i]->type == METACHAR_APPEND_REDIRECT)
// 	{
// 		if (tokens[*i + 1])
// 		{
// 			file = tokens[++(*i)]->word;
// 			fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
// 			if (fd < 0)
// 			{
// 				perror("handle_append: open file");
// 				return;
// 			}
// 			cmd->append_fd = fd;
// 		}
// 		else
// 			perror("handle_append: no file provided after '>>'");
// 		++(*i);
// 	}
// 	else
// 	{
// 		perror("handle_append: expected '>>' before file name");
// 	}
// }

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
