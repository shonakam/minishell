/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoshker <kmoshker@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 06:55:51 by mosh              #+#    #+#             */
/*   Updated: 2024/03/21 09:15:21 by kmoshker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "get_next_line.h"
#include "libft.h"

static char	*ft_strljoin(char *s1, char *s2)
{
	char	*new;

	if (!s1 && !s2)
	{
		free (s1);
		return (NULL);
	}
	else if (!s1)
	{
		free (s1);
		return (ft_strdup(s2));
	}
	else if (!s2)
		return (ft_strdup(s1));
	new = (char *)malloc((ft_istrlen(s1) + ft_istrlen(s2) + 1) * sizeof(char));
	if (!new)
		return (NULL);
	new[0] = '\0';
	ft_strcat(new, s1);
	ft_strcat(new, s2);
	free (s1);
	return (new);
}

	// char		develop[BUFFER_SIZE + 1];
static char	*develop_remember_me(char *remember_me, int fd)
{
	char		*develop;
	int			bytes_to_read;

	develop = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!develop)
		exit (1);
	bytes_to_read = 1;
	while (bytes_to_read > 0 && !ft_strchr(remember_me, '\n'))
	{
		bytes_to_read = read(fd, develop, BUFFER_SIZE);
		if (bytes_to_read <= -1)
			return (NULL);
		if (bytes_to_read == 0
			&& (!remember_me || ft_istrlen(remember_me) == 0))
		{
			if (remember_me)
				free(remember_me);
			return (NULL);
		}
		develop[bytes_to_read] = '\0';
		remember_me = ft_strljoin(remember_me, develop);
	}
	return (remember_me);
}

static char	*output_line_until(char *remember_me)
{
	int		i;
	char	*output_line;

	i = 0;
	if (!remember_me)
		return (NULL);
	while (remember_me[i] && remember_me[i] != '\n')
		i++;
	output_line = malloc(sizeof(char) * (i + 2));
	if (!output_line)
		return (NULL);
	i = 0;
	while (remember_me[i] && remember_me[i] != '\n')
	{
		output_line[i] = remember_me[i];
		i++;
	}
	if (remember_me[i] == '\n')
		output_line[i] = remember_me[i];
	output_line[i + 1] = '\0';
	return (output_line);
}

static char	*delete_and_renew(char *remember_me)
{
	int		i;
	int		j;
	char	*forget_me;

	i = 0;
	while (remember_me[i] && remember_me[i] != '\n')
		i++;
	if (remember_me[i] == '\n')
		i++;
	forget_me = malloc(sizeof(char) * (ft_istrlen(remember_me) - i + 1));
	if (!forget_me)
		return (NULL);
	j = 0;
	while (remember_me[i])
		forget_me[j++] = remember_me[i++];
	forget_me[j] = '\0';
	free (remember_me);
	if (ft_istrlen(forget_me) == 0)
	{
		free (forget_me);
		return (NULL);
	}
	return (forget_me);
}

char	*get_next_line(int fd)
{
	static char	*remember_me[OPEN_MAX];
	char		*output_line;

	if (fd < 0 || fd >= OPEN_MAX || BUFFER_SIZE <= 0)
		return (0);
	remember_me[fd] = develop_remember_me(remember_me[fd], fd);
	if (!remember_me[fd] || ft_istrlen(remember_me[fd]) == 0)
	{
		free(remember_me[fd]);
		return (NULL);
	}
	output_line = output_line_until(remember_me[fd]);
	remember_me[fd] = delete_and_renew(remember_me[fd]);
	return (output_line);
}
