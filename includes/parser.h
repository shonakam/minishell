/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 23:54:54 by shonakam          #+#    #+#             */
/*   Updated: 2024/09/12 23:54:55 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PAESER_H

typedef struct	s_command {
	char				**argv;
	int					argc;
	struct s_command	*next;
}				t_command;

typedef struct	s_pipe {
	int	read_end;
	int	write_end;
}				t_pipe;

t_command	*set_argument(t_command *cmd, char *token);
void		handle_io_redirect(t_command *cmd, t_token **tokens, int *i);
void		handle_append(t_command *cmd, t_token **tokens, int *i);
void		handle_heredoc(t_command *cmd, t_token **tokens, int *i);

#endif