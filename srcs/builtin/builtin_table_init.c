#include "builtin_internal.h"

static void	register_builtin(t_builtin *entry, char *name, t_builtin_func func)
{
	entry->name = name;
	entry->len = ft_strlen(name);
	entry->func = func;
}

bool	builtin_table_init(t_context *ctx)
{
	ctx->builtins = x_calloc(BUILTIN_SIZE + 1, sizeof(t_builtin));
	if (!ctx->builtins)
		return (false);
	register_builtin(&ctx->builtins[B_ECHO], "echo", ft_echo);
	register_builtin(&ctx->builtins[B_CD], "cd", ft_cd);
	register_builtin(&ctx->builtins[B_PWD], "pwd", ft_pwd);
	register_builtin(&ctx->builtins[B_EXPORT], "export", ft_export);
	register_builtin(&ctx->builtins[B_UNSET], "unset", ft_unset);
	register_builtin(&ctx->builtins[B_ENV], "env", ft_env);
	register_builtin(&ctx->builtins[B_EXIT], "exit", ft_exit);
	return (true);
}
