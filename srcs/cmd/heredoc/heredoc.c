/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 07:44:40 by shonakam          #+#    #+#             */
/*   Updated: 2024/09/21 01:52:40 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static void	*heredoc_loop(int fd, char *delimiter, int s, t_envlist *e)
{
	char	*line;
	char	*processed_line;

	while (1)
	{
		line = readline("heredoc> ");
		if (line == NULL)
			return (ft_putendl_fd(static_err_msg(1), STDOUT_FILENO), NULL);
		if ((ft_strlen(line) == ft_strlen(delimiter)) &&
			ft_strncmp(line, delimiter, ft_strlen(line)) == 0)
			return (free(line), NULL);
		processed_line = expand_variables(line, s, e);
		if (processed_line == NULL)
		{
			free(line);
			continue ;
		}
		ft_putendl_fd(processed_line, fd);
		free(processed_line);
		free(line);
	}
	return (NULL);
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

static t_heredoc	*set_heredoc(char *del, int *index, int s, t_envlist *e)
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
	heredoc_loop(fd, del, s, e);
	return (create_hd_node(filename, fd));
}

/*
-- '<<'が存在するか確認
-- delimiterの取得 展開
-- tmpファイルを作成(READ&WRITE)
-- LOOP開始
-- 終了後closeは外部で処理
-- 1コマンド1heredoc

--	bash-3.2$ cat s1 e s2
	s1-hi
	cat: e: No such file or directory
	s2-hoo
-- tmpファイルを作成するから問題ない
*/
int	handle_heredoc(t_command *cmd, int *index, int s, t_envlist *e)
{
	int		flag;
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
					set_heredoc(cmd->argv[i + 1], index, s, e));
			}
		}
		i++;
	}
	return (flag);
}
