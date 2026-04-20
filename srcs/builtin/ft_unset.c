#include "builtin_internal.h"

int	ft_unset(t_context *ctx, char **argv)
{
	int		i;
	int		exit_status;

	i = 1;
	exit_status = EXIT_SUCCESS;
	if (!argv[1])
		return (EXIT_SUCCESS);
	while (argv[i])
	{
		if (!is_valid_identifier(argv[i]))
		{
			ft_dprintf(STDERR_FILENO, ERR_INVALID_ID_UNSET, argv[i]);
			exit_status = EXIT_FAILURE;
		}
		else
		{
			env_list_remove(&ctx->env_list, argv[i]);
		}
		i++;
	}
	return (exit_status);
}
