/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 07:44:40 by shonakam          #+#    #+#             */
/*   Updated: 2024/09/12 18:23:45 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static void	heredoc_loop(int fd, char *delimiter)
{
	char	*line;

	while (1)
	{
		line = readline("heredoc> ");
		if (line == NULL)
			break ;
		if ((ft_strlen(line) == ft_strlen(delimiter))
			&& ft_strncmp(line, delimiter, ft_strlen(line)) == 0)
		{
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	
}

/*
-- delImiterの取得
-- tmpファイルを作成(READ&WRITE)
-- LOOP開始
-- 終了後closeは外部で処理
*/
void	handle_heredoc(t_command *cmd, t_token **tokens, int *i)
{
	char	*delimiter;
	int		fd;

	if (!tokens[++(*i)] || tokens[*i]->type != METACHAR_NONE)
		return (perror("handle_heredoc: missing delimiter\n"));
	delimiter = tokens[*i]->word;
	fd = open("heredoc_temp_file", O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return (perror("handle_heredoc: open file"));
	heredoc_loop(fd, delimiter);
	// cmd->input_fd = fd;
}
