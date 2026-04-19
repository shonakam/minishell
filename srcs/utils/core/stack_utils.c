#include "../utils_internal.h"

// https://man7.org/linux/man-pages/man1/bash.1.html#:~:text=Values%20are%20in,a%20new%20limit.
// bool	is_stack_overflow(void *base)
// {
// 	int		current;
// 	size_t	usage;

// 	if (!base)
// 		return (false);
// 	usage = (size_t)base - (size_t)&current;
// 	return (usage > (STACK_LIMIT * 1024));
// }
