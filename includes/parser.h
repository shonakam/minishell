/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 23:54:54 by shonakam          #+#    #+#             */
/*   Updated: 2024/09/20 16:43:21 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

typedef struct	s_heredoc {
	char				*filename;
	int					hd_fd;
	struct s_heredoc	*prev;
	struct s_heredoc 	*next;
}				t_heredoc;

typedef struct	s_command {
	char				**argv;
	int					argc;
	t_heredoc			*hd_list;
	struct s_command	*next;
}				t_command;

typedef struct	s_pipe {
	int	read_end;
	int	write_end;
}				t_pipe;

t_command	*set_argument(t_command *cmd, char *token);

#endif