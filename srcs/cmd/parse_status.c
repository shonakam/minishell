/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_status.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 09:50:44 by shonakam          #+#    #+#             */
/*   Updated: 2024/10/03 12:15:13 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

/*
正常終了したかどうかを判定
0x7f (127) はシグナルマスク
*/
static int	ft_wifexited(int status)
{
	return ((status & 0x7f) == 0);
}
/* 
正常終了した場合の終了ステータスを取得
8ビット右シフトし、上位8ビットをマスク
*/
static int	ft_wexitstatus(int status)
{
	return ((status >> 8) & 0xff);
}
/*
シグナルで終了したかどうか
下位7ビットにシグナル番号がある場合
*/
static int ft_wifsignaled(int status)
{
	return ((status & 0x7f) != 0 && (status & 0x7f) != 0x7f);
}
/*
シグナルで終了した場合のシグナル番号を取得
下位7ビットがシグナル番号
*/
static int ft_wtermsig(int status)
{
	return (status & 0x7f);
}

int	parse_exit_status(int status)
{
	int	exit_code;

	if (ft_wifexited(status))
	{
		exit_code = ft_wexitstatus(status);
		return (exit_code);
	}
	else if (ft_wifsignaled(status))
	{
		exit_code = ft_wtermsig(status) + 128;
		return (exit_code);
	}
	else
		return (-1);
}
