/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 23:54:07 by shonakam          #+#    #+#             */
/*   Updated: 2024/09/14 17:19:58 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_BUILTIN_H
# define FT_BUILTIN_H

int	is_builtin(t_command *cmd);
int	builtin_runner(t_command *cmd, int fd);

int	cmd_exit(t_command *cmd, int fd);
int	cmd_pwd(t_command *cmd, int fd);

#endif