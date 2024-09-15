/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 07:44:40 by shonakam          #+#    #+#             */
/*   Updated: 2024/09/15 23:33:09 by shonakam         ###   ########.fr       */
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

t_heredoc	*create_hd_node(char *filename, int fd)
{
	t_heredoc	*new_node;

	new_node = (t_heredoc *)malloc(sizeof(t_heredoc));
	if (new_node == NULL)
		return (perror("create_hd_node: malloc failed"), NULL);
	new_node->filename = strdup(filename);
	if (new_node->filename == NULL)
	{
		perror("strdup failed");
		free(new_node);
		return NULL;
	}
	new_node->hd_fd = fd;
	new_node->filename = filename;
	new_node->prev = NULL;
	new_node->next = NULL;
	return (new_node);
}

void	append_hd_node(t_heredoc **head, t_heredoc *new_node)
{
		t_heredoc *last;

		last = *head;
		if (*head == NULL)
		{
			*head = new_node;
			return;
		}
		while (last->next != NULL)
			last = last->next;
		last->next = new_node;
		new_node->prev = last;
}

static t_heredoc	*set_heredoc(char *delimiter, int *index)
{
	int		fd;
	char	*filename;

	fd = -1;
	while (fd < 0)
	{
		filename = concat_vars(2, "/tmp/heredoc_temp_file_", ft_itoa(*index));
		fd = open(filename, O_RDWR | O_CREAT | O_TRUNC, 0644);
		if (fd < 0)
		{
			free(filename);
			(*index)++;
		}
	}
	(*index)++;
	heredoc_loop(fd, delimiter);
	return (create_hd_node(filename, fd));
}

/*
-- '<<'が存在するか確認
-- delimiterの取得
-- tmpファイルを作成(READ&WRITE)
-- LOOP開始
-- 終了後closeは外部で処理
-- 1コマンド1heredoc
*/
int	handle_heredoc(t_command *cmd, int *index)
{
	int		flag;
	int		fd;
	int		i;

	i = 0;
	flag = 0;
	while (cmd->argv && cmd->argv[i])
	{
		if (ft_strcmp(cmd->argv[i], "<<") == 0)
		{
			if (i == 0)
				flag = 1;
			if (cmd->argv[i + 1])
			{
				append_hd_node(&cmd->hd_list,
					set_heredoc(cmd->argv[i + 1], index));
				// return (flag);
			}
		}
		i++;
	}
	return (flag);
}
