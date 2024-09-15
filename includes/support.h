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

/*  <=== lexer/parser ===>  */
int			count_cmd(t_command *cmd);
void		cpy_args(t_command *cmd, char **a);
void		free_commands(t_command *cmd);
t_command	*get_current_cmd(t_command *cmd, int depth);

/* <=== executor/support ===>  */
int			is_executable(const char *path);
void		print_error(const char *msg, const char *cmd);
void		redirect_fd(int old, int new);
void		free_heredoc(t_command *cmd);

#endif
