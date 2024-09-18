#ifndef SUPPORT_H
# define SUPPORT_H

/*  <=== env/support ===>  */
char		**ft_split_by_eq(char *s);
int			get_listsize(t_envlist **l);
void		free_envlist(t_envlist **l);
char		*get_bin_path(t_envlist *list, char *cmd);
t_envlist	*create_head_node(void);

/*  <=== lexer/support ===>  */
int			ft_isspace(char c);
int			valid_quote(const char *s);
int			count_tokens(t_token **tokens);
void		free_tokens(t_token **tokens);
char		*connect_and_free(char *s1, char *s2);
int			handle_special_char_size(const char *line, size_t position);
TokenType	identify_metachar(const char *input, size_t pos);

/*  <=== parser/support ===>  */
int			count_cmd(t_command *cmd);
void		cpy_args(t_command *cmd, char **a);
void		free_argv(char	**argv);
void		free_commands(t_command *cmd);
t_command	*get_current_cmd(t_command *cmd, int depth);

/* <=== executor/support ===>  */
int			is_executable(const char *path);
void		print_error(const char *msg, const char *cmd);
void		redirect_fd(int old, int new);
void		free_heredoc(t_command *cmd);
void		handle_pipe(int *p, int f);
char		**rebuild_args(t_command *cmd);
char		*get_next_hd_filename(t_heredoc **hd);
int			count_hd(t_heredoc *hd);
int			is_here_doc_placeholder(const char *arg);
char		*concat_and_free(char *result, char *tmp);

#endif
