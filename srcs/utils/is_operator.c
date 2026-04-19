#include "utils_internal.h"

int	is_operator(const char *str)
{
	if (!str || !*str)
		return (0);
	if (ft_strncmp(str, OP_HEREDOC, 2) == 0 ||
		ft_strncmp(str, OP_APPEND, 2) == 0 ||
		ft_strncmp(str, OP_AND_IF, 2) == 0 ||
		ft_strncmp(str, OP_OR_IF, 2) == 0)
		return (2);
	if (ft_strchr(OPERATOR_CHARS, *str))
		return (1);
	return (0);
}
