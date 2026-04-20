#ifndef BUILTIN_INTERNAL_H
# define BUILTIN_INTERNAL_H

# include "../libft/libft.h"
# include "error.h"
# include "session.h"
# include "builtin.h"
# include "utils.h"

typedef enum e_builtin_type {
	B_ECHO = 0,
	B_CD,
	B_PWD,
	B_EXPORT,
	B_UNSET,
	B_ENV,
	B_EXIT,
	BUILTIN_SIZE
}	t_builtin_type;

bool	is_valid_identifier(const char *s);
void	print_sorted_export(t_context *ctx);

int		ft_echo(t_context *ctx, char **argv);
int		ft_cd(t_context *ctx, char **argv);
int		ft_pwd(t_context *ctx, char **argv);
int		ft_export(t_context *ctx, char **argv);
int		ft_unset(t_context *ctx, char **argv);
int		ft_env(t_context *ctx, char **argv);
int		ft_exit(t_context *ctx, char **argv);

#endif /* BUILTIN_INTERNAL_H */
