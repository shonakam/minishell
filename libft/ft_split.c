/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 09:07:58 by kmoshker          #+#    #+#             */
/*   Updated: 2025/02/09 03:50:26 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	free_split(char **split)
{
	int	i;

	i = 0;
	if (!split)
		return ;
	while (split[i])
		free(split[i++]);
	free(split);
}

static char	*get_next_word(char const **s, char c)
{
	char	*word;
	int		len;

	while (**s == c)
		(*s)++;
	len = 0;
	while ((*s)[len] && (*s)[len] != c)
		len++;
	word = (char *)malloc(len + 1);
	if (!word)
		return (NULL);
	ft_strlcpy(word, *s, len + 1);
	*s += len;
	return (word);
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	int		i;

	if (!s)
		return (NULL);
	result = (char **)malloc(sizeof(char *) * (count_words(s, c) + 1));
	if (!result)
		return (NULL);
	i = 0;
	while (*s)
	{
		if (*s != c)
		{
			result[i] = get_next_word(&s, c);
			if (!(result[i]))
				return (free_split(result), NULL);
			i++;
		}
		else
			s++;
	}
	result[i] = NULL;
	return (result);
}

// int main(void)
// {
//     char *str = "                     ";
//     char charset = 'a';
//     char **result;

//     result = ft_split(str, charset);

//     for (int i = 0; result[i]; i++)
//     {
//         printf("'%s'\n", result[i]);
//         free(result[i]);
//     }
//     free(result);
//     return (0);
// }