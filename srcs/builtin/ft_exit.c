#include "builtin_internal.h"

static bool	is_numeric(char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (false);
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (!str[i])
		return (false);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (false);
		i++;
	}
	return (true);
}

int	ft_exit(t_context *ctx, char **argv)
{
	if (!ctx->in_pipeline)
		ft_putendl_fd("exit", STDERR_FILENO);
	if (!argv[1])
		exit(ctx->last_status);
	if (!is_numeric(argv[1]))
	{
		ft_dprintf(STDERR_FILENO, ERR_EXIT_NUMERIC, argv[1]);
		return (STATUS_SYNTAX_ERR);
	}
	if (argv[2])
	{
		ft_dprintf(STDERR_FILENO, ERR_TOO_MANY_ARGS, "exit");
		return (STATUS_SYNTAX_ERR);
	}
	ctx->exit = true;
	return ((unsigned char)ft_atoi(argv[1]));
}
