/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolve_eos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 17:48:22 by shonakam          #+#    #+#             */
/*   Updated: 2025/02/09 11:04:25 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static int	get_last_non_space_index(const char *line, size_t i)
{
	while (line[i])
		i++;
	if (i == 0)
		return (-1);
	while (--i > 0 && ft_isspace((unsigned char)line[i]))
		;
	return ((int)i);
}

static int	check_unfinished(const char *line)
{
	int	i;

	i = get_last_non_space_index(line, 0);
	if (i < 0)
		return (0);
	if (line[i] == '|')
	{
		if (i > 0 && line[i - 1] == '|')
			return (-5);
		return (1);
	}
	if (line[i] == '<')
	{
		if (i > 0 && line[i - 1] == '<')
			return (-1);
		return (-2);
	}
	if (line[i] == '>')
	{
		if (i > 0 && line[i - 1] == '>')
			return (-4);
		return (-3);
	}
	return (0);
}

static char	*resolve_reserve(char *line)
{
	char	*new_line;
	int		unfinished_flag;

	unfinished_flag = check_unfinished(line);
	while (unfinished_flag)
	{
		if (unfinished_flag < 0)
		{
			syntax_err(unfinished_flag);
			return (free(line), NULL);
		}
		else if (unfinished_flag == 1)
			new_line = readline("pipe> ");
		if (!new_line)
			return (free(new_line), NULL);
		if (ft_strspn(new_line, " \t\n") == strlen(new_line))
		{
			free(new_line);
			continue ;
		}
		line = connect_and_free(line, new_line);
		unfinished_flag = check_unfinished(line);
	}
	return (line);
}

char	*resolve_eos(char *line)
{
	char	*new_line;

	if (line && line[0] == '|')
		return (syntax_err(-9), NULL);
	new_line = ft_strdup(line);
	if (!new_line)
		return (NULL);
	new_line = resolve_reserve(new_line);
	return (new_line);
}
