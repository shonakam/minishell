#include <unistd.h>

int	putchar_int(int c)
{
	return (write(STDOUT_FILENO, &c, 1));
}
