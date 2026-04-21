#include "builtin_internal.h"

bool	builtin_table_init(t_context *ctx)
{
	static const t_builtin	g_builtin_table[] = {
	[B_ECHO] = {"echo", 4, ft_echo},
	[B_CD] = {"cd", 2, ft_cd},
	[B_PWD] = {"pwd", 3, ft_pwd},
	[B_EXPORT] = {"export", 6, ft_export},
	[B_UNSET] = {"unset", 5, ft_unset},
	[B_ENV] = {"env", 3, ft_env},
	[B_EXIT] = {"exit", 4, ft_exit},
	{NULL, 0, NULL}
	};

	ctx->builtins = g_builtin_table;
	return (true);
}
