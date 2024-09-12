/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolve_eos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 17:48:22 by shonakam          #+#    #+#             */
/*   Updated: 2024/09/12 14:55:58 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

// quoteが奇数の場合,奇数番めが先に来た方のreadlineを再開
static int	get_quote_flag(const char *line)
{
	int	single_quote_flag;	// ' のカウント
	int	double_quote_flag;	// " のカウント
	int	i;

	double_quote_flag = 0;
	single_quote_flag = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] == '\'' && double_quote_flag == 0)		// ダブルクォート内ではシングルクォートは無視
			single_quote_flag = !single_quote_flag;			// 奇数回目と偶数回目で切り替える
		else if (line[i] == '\"' && single_quote_flag == 0)	// シングルクォート内ではダブルクォートは無視
			double_quote_flag = !double_quote_flag;			// 奇数回目と偶数回目で切り替える
		i++;
	}
	// シングルクォートまたはダブルクォートが奇数回なら未完了
	return (single_quote_flag || double_quote_flag);
}

static int	is_unfinished(const char *line)
{
	size_t	i;

	i = 0;
	while (line[i])
		i++;
	if (i == 0)
		return (0);
	i--;
	while (i > 0 && (line[i] == ' ' || (9 <= line[i] && line[i] <= 13)))
		i--;
	if (line[i] == '|')
		return (1);
	if (line[i] == '<')
		return (2);
	if (line[i] == '>')
		return (3);
	if (ft_strncmp(&line[i], ">>", 2) == 0)
		return (4);
	return (0);
}

static char	*resolve_quote(char *line)
{
	char	*new_line;
	int		quote_flag;

	quote_flag = get_quote_flag(line);
	while (quote_flag)
	{
		new_line = readline("quote> ");
		if (!new_line)
			return (free(new_line), NULL);
		line = connect_and_free(line, new_line);
		quote_flag = get_quote_flag(line);
	}
	return (line);
}

static char	*resolve_reserve(char *line)
{
	char	*new_line;
	int		unfinished_flag;

	unfinished_flag = is_unfinished(line);
	while (unfinished_flag)
	{
		if (unfinished_flag == 1)								// パイプ '|' の場合
			new_line = readline("pipe> ");
		else if (unfinished_flag == 2)							// リダイレクト '<' の場合
			new_line = readline("heredoc> ");
		else if (unfinished_flag == 3 || unfinished_flag == 4)	// リダイレクト '>' の場合
			new_line = readline("> ");							// ここはエラーにすべきかも
		if (!new_line)
			return (free(new_line), NULL);
		line = connect_and_free(line, new_line);
		unfinished_flag = is_unfinished(line);
	}
	return (line);
}

/*
	eos = end of sentence
	quote check
	eos char check
*/
char	*resolve_eos(char *line)
{
	char	*new_line;
	int		quote_flag;
	int		unfinished_flag;

	new_line = ft_strdup(line);
	new_line = resolve_quote(new_line);
	new_line = resolve_reserve(new_line);
	// printf("result: %s\n", new_line);	// 結果を表示
	return (new_line);
}
