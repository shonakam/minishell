#include <unistd.h>

void	debug_print_green_line(void)
{
    const char *green = "\033[32m";
    const char *reset = "\033[0m";
	const char *c20 = "--------------------";
    int         i;

    write(STDOUT_FILENO, green, 5);
    i = 0;
    while (i < 4)
    {
        write(STDOUT_FILENO, c20, 20);
        i++;
    }
    write(STDOUT_FILENO, reset, 4);
    write(STDOUT_FILENO, "\r\n", 2);
}
