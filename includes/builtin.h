#ifndef BUILTIN_H
# define BUILTIN_H

struct s_context;
typedef struct s_context t_context;

typedef int (*t_builtin_func)(t_context *ctx, char **argv);

typedef struct s_builtin {
	char			*name;
	size_t			len;
	t_builtin_func	func;
}   t_builtin;

bool            builtin_table_init(t_context *ctx);
t_builtin_func	get_builtin_func(t_context *ctx, char *cmd);

#endif /* BUILTIN_H */
