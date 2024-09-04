#ifndef SUPPORT_H
# define SUPPORT_H

// <=== lexer/support ===>
int	ft_isspace(char c);
int	valid_quote(const char *s);
void	print_tokens(t_token **tokens);

// <=== executor/support ===>
int	count_pipechar(t_token **tokens);

#endif
