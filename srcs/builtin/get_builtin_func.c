#include "builtin_internal.h"

t_builtin_func	get_builtin_func(t_context *ctx, char *cmd)
{
	size_t	i;
	size_t	len;

	if (!cmd || !ctx || !ctx->builtins)
		return (NULL);
	i = 0;
	len = ft_strlen(cmd);
	while (ctx->builtins[i].name != NULL)
	{
		if (ctx->builtins[i].len == len &&
			ft_strncmp(cmd, ctx->builtins[i].name, len) == 0)
			return (ctx->builtins[i].func);
		i++;
	}
	return (NULL);
}
