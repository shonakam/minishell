/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 00:52:47 by mosh              #+#    #+#             */
/*   Updated: 2024/09/21 01:38:02 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

// コマンド構造体を作成する関数
t_command	*create_command(void)
{
	t_command *cmd;
	
	cmd = (t_command *)malloc(sizeof(t_command));
	if (!cmd) {
		perror("create_command: malloc");
		exit(EXIT_FAILURE);
	}
	cmd->argv = NULL;
	cmd->argc = 0;
	cmd->hd_list = NULL;
	cmd->next = NULL;
	return (cmd);
}

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
		if (!args[cmd->argc - 2])
			return (free(args), NULL);
	}
	args[cmd->argc - 1] = ft_strdup(token);
	if (!args[cmd->argc - 1])
		return (free(args), perror("set_argument: malloc arg"), NULL);
	args[cmd->argc] = NULL;
	cmd->argv = args;
	return (cmd);
}

t_command	*build_commands(t_token **tokens, int count)
{
	t_command	*head;
	t_command	*current;
	int			i;

	head = create_command();
	current = head;
	i = 0;
	while (i < count && tokens[i])
	{
		if (tokens[i]->type == METACHAR_PIPE)
		{
			if (!tokens[++i])
				return (head);
			current->next = create_command();
			current = current->next;
		}
		else
			current = set_argument(current, tokens[i++]->word);
	}
	return (head);
}
