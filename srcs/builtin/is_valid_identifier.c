#include "builtin_internal.h"

/*
 * is_valid_identifier:
 * Check if the string is a valid shell identifier.
 * Must start with a letter or underscore, followed by letters, numbers, or underscores.
 */
bool	is_valid_identifier(const char *s)
{
	int	i;

	if (!s || (!ft_isalpha(s[0]) && s[0] != '_'))
		return (false);
	i = 1;
	while (s[i])
	{
		if (!ft_isalnum(s[i]) && s[i] != '_')
			return (false);
		i++;
	}
	return (true);
}