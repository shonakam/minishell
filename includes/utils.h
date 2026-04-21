#ifndef UTILS_H
# define UTILS_H

# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdbool.h>
# include "../libft/libft.h"
# include "session.h"

struct s_ast_node;
typedef struct s_ast_node t_ast_node;

void	free_matrix(char **matrix);
char	*join_three(const char *s1, const char *s2, const char *s3);
int		x_dup(int fd);
int		x_dup2(int oldfd, int newfd);
bool	x_fork(pid_t *pid);
int		x_open(char *path, int flags, mode_t mode);
bool	x_pipe(int pipefd[2]);
void	*x_calloc(size_t count, size_t size);
void	*x_realloc(void *ptr, size_t old_size, size_t new_size);
t_list	*x_lstnew(void *content);
char	*x_strdup(const char *s);
char	*x_strndup(const char *s, size_t n);
char	*x_substr(char const *s, unsigned int start, size_t len);


int	is_operator(const char *str);
int	is_redirect(const char *str);

bool	is_stack_overflow(void *base);

# ifdef DEBUG_MODE
void	d(void);
void	debug_print_ast(t_ast_node *ast);
void	debug_print_env(void *content);
void	debug_print_job(t_context *ctx);
void	debug_print_list(t_list *list, void (*f)(void *));
void	debug_print_token(void *content);
void	*debug_print_memory(void *addr, unsigned int size);
void	debug_print_green_line(void);
# else
# define d() ((void)0)
# define debug_print_ast(ast) ((void)0)
# define debug_print_env(content) ((void)0)
# define debug_print_job(t_context) ((void)0)
# define debug_print_list(list, f) ((void)0)
# define debug_print_token(content) ((void)0)
# define debug_print_memory(addr, size) ((void)0)
# define debug_print_green_line() ((void)0)
# endif

#endif /* UTILS_H */
