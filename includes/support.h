#ifndef SUPPORT_H
# define SUPPORT_H

/*  <=== env/support ===>  */
// int		check_null_envlist_member(t_envlist *l);
char	**ft_split_by_eq(char *s);

/*  <=== lexer/support ===>  */
int		ft_isspace(char c);
int		valid_quote(const char *s);
void	print_tokens(t_token **tokens);

/* <=== executor/support ===>  */
int		count_pipechar(t_token **tokens);

#endif
