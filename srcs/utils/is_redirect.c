#include "utils_internal.h"

int	is_redirect(const char *str)
{
	if (!str || !*str)
		return (0);
	if (ft_strlen(str) == 1)
		return (str[0] == '>' || str[0] == '<');
	if (ft_strlen(str) == 2)
	{
		return ((str[0] == '>' && str[1] == '>') ||
				(str[0] == '<' && str[1] == '<'));
	}
	return (0);
}
