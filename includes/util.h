/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 13:11:37 by shonakam          #+#    #+#             */
/*   Updated: 2025/02/19 22:14:49 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTIL_H
# define UTIL_H

int			is_executable(const char *path);

/* <=== TOKEN ===> */
int			count_tokens(t_token **tokens);
int			find_quotes(const char *token);
int			valid_quote(const char *s);
void		free_tokens(t_token **tokens);

/* <=== COMMAND ===> */
void		free_commands(t_command *cmd);
void		free_argv(char	**argv);
void		cpy_args(t_command *cmd, char **a);
int			count_cmd(t_command *cmd);
t_command	*get_current_cmd(t_command *cmd, int depth);

/* <=== HEREDOCUMENT ===> */
void		free_heredoc(t_command *cmd);
int			count_hd(t_heredoc *hd);
int			is_here_doc_placeholder(const char *arg);
char		*get_next_hd_filename(t_heredoc **hd);
int			check_delimiter(char *line, char *delimiter);

/* <=== REDIRECT ===> */
// void		handle_pipe(int *p, int flag);
// void		redirect_fd(int old, int new);
int			get_redirect_mode(char *arg);
int			check_fd(int fd);

/* <=== EXPAND ===> */
char		*concat_and_free(char *result, char *tmp);
void		spinlock(void);

/* <=== DEBUG ===> */
void		print_tokens(t_token **tokens);
void		print_commands(t_command *cmd);
void		print_argv(char **argv);
void		d(void);

#endif
