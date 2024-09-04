#ifndef SUPPORT_H
# define SUPPORT_H

/*  <=== env/support ===>  */
char	**ft_split_by_eq(char *s);
int		get_listsize(t_envlist **l);

/*  <=== lexer/support ===>  */
int		ft_isspace(char c);
int		valid_quote(const char *s);
void	free_tokens(t_token **tokens);
void	print_tokens(t_token **tokens);
int		count_tokens(t_token **tokens);

/*  <=== lexer/parser ===>  */
void	cpy_args(t_command *cmd, char **a);

/* <=== executor/support ===>  */
int		count_pipechar(t_token **tokens);

#endif
