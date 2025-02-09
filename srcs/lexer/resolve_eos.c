/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolve_eos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 17:48:22 by shonakam          #+#    #+#             */
/*   Updated: 2025/02/04 20:06:57 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

char	*connect_and_free(char *s1, char *s2)
{
	char	*result;

	result = concat_vars(4, "\n", s1, "\n", s2);
	return (free(s1), result);
}

static int	is_unfinished(const char *line, size_t i)
{
	while (line[i])
		i++;
	if (i == 0)
		return (0);
	while (--i > 1 && ft_isspace((unsigned char)line[i]))
		i--;
	if (i >= 0 && line[i] == '|')
	{
		if (i > 0 && line[i - 1] == '|')
			return (-5);
		return (1);
	}
	if (i >= 0 && line[i] == '<')
	{
		if (i > 0 && line[i - 1] == '<')
			return (-1);
		return (-2);
	}
	if (i >= 0 && line[i] == '>')
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

	unfinished_flag = is_unfinished(line, 0);
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
		line = connect_and_free(line, new_line);
		unfinished_flag = is_unfinished(line, 0);
	}
	return (line);
}

/*
	quote check
	eos char check
*/
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
