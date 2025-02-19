/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 14:00:46 by shonakam          #+#    #+#             */
/*   Updated: 2025/02/19 14:13:16 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_H
# define COMMAND_H

typedef struct s_token	t_token;

typedef struct s_heredoc {
	char				*filename;
	int					hd_fd;
	struct s_heredoc	*next;
}				t_heredoc;

typedef struct s_command {
	unsigned int		track;
	char				**argv;
	int					argc;
	t_heredoc			*hd_list;
	struct s_command	*next;
}				t_command;

#endif