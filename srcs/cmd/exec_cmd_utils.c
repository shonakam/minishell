/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 03:14:41 by shonakam          #+#    #+#             */
/*   Updated: 2024/09/07 07:03:11 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

// int	handle_pipe_io(t_token **token, int *fds, int fd_i, int flag)
// {
// 	if (flag == 0 && 0 < count_pipe(token))
// 	{
// 		if (fd_i > 0)
// 		{
// 			if (dup2(fds[fd_i - 2], STDIN_FILENO) == -1)
// 				return (perror("hamdle_pipe_io: dup2 input"), -1);
// 		}
// 		if (fd_i + 1 < (count_pipe(token) * 2))
// 		{
// 			if (dup2(fds[fd_i], STDOUT_FILENO) == -1)
// 				return (perror("hamdle_pipe_io: dup2 output"), -1);
// 		}
// 	}
// 	else if (flag == 1 && 0 < count_pipe(token))
// 	{
// 		close(fds[fd_i]);
// 		if (fd_i > 0)
// 			close(fds[fd_i - 2]);
// 		return (0);
// 	}
// 	return (0);
// }
