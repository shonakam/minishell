/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 13:11:37 by shonakam          #+#    #+#             */
/*   Updated: 2025/02/14 22:34:21 by shonakam         ###   ########.fr       */
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
void		handle_pipe(t_command *cmd, int *p, int flag);
void		redirect_fd(int old, int new);
int			get_redirect_mode(char *arg);

/* <=== EXPAND ===> */
char		*concat_and_free(char *result, char *tmp);

/* <=== DEBUG ===> */
void		print_tokens(t_token **tokens);
void		print_commands(t_command *cmd);
void		print_argv(char **argv);
void		pe(void);

#endif
