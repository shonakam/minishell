#include "builtin_internal.h"

static bool	is_n_option(char *arg)
{
	size_t	i;

	if (!arg || arg[0] != '-' || arg[1] != 'n')
		return (false);
	i = 2;
	while (arg[i])
	{
		if (arg[i++] != 'n')
			return (false);
	}
	return (true);
}

int	ft_echo(t_context *ctx, char **argv)
{
	size_t	i;
	bool	newline;

	(void)ctx;
	newline = true;
	i = 1;
	while (argv[i] && is_n_option(argv[i]))
	{
		newline = false;
		i++;
	}
	while (argv[i])
	{
		ft_putstr_fd(argv[i], STDOUT_FILENO);
		if (argv[i + 1])
			ft_putstr_fd(" ", STDOUT_FILENO);
		i++;
	}
	if (newline)
		ft_putstr_fd("\n", STDOUT_FILENO);
	return (EXIT_SUCCESS);
}
