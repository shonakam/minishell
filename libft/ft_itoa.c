/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 01:40:32 by kmoshker          #+#    #+#             */
/*   Updated: 2024/09/24 05:42:50 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*make_new(char *new, int n, int is_minus, int count)
{
	new[count] = '\0';
	while (n)
	{
		if (is_minus)
			new[count - 1] = -(n % 10) + '0';
		else
			new[count - 1] = (n % 10) + '0';
		count--;
		n /= 10;
	}
	if (is_minus)
		new[0] = '-';
	return (new);
}

char	*ft_itoa(int n)
{
	char	*new;
	int		count;
	int		n_for_count;
	int		is_minus;

	if (n == 0)
		return (ft_strdup("0"));
	count = 0;
	is_minus = 0;
	if (n < 0)
	{
		count++;
		is_minus = 1;
	}
	n_for_count = n;
	while (n_for_count != 0)
	{
		n_for_count /= 10;
		count++;
	}
	new = (char *)malloc((count + 1) * sizeof(char));
	if (!new)
		return (NULL);
	return (make_new(new, n, is_minus, count));
}

// #include <stdio.h>
// #include <stdlib.h>
// int main(int argc, char **argv)
// {
//     if (argc != 2) {
//         printf("Usage: %s <integer>\n", argv[0]);
//         return 1;
//     }

//     // コマンドライン引数を整数に変換
//     int number = atoi(argv[1]);

//     // ft_itoa を使って整数を文字列に変換
//     char *result = ft_itoa(number);

//     if (result) {
//         // 結果を表示
//         printf("The string representation of %d is: %s\n", number, result);
//         free(result);  // メモリ解放
//     } else {
//         printf("Memory allocation failed\n");
//     }

//     return 0;
// }