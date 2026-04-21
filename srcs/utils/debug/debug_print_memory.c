#include <unistd.h>
#include <stdint.h>
#include <limits.h>

static void	print_hex_byte(unsigned char byte)
{
	static const char *hex_chars = "0123456789abcdef";

	write(STDOUT_FILENO, &hex_chars[byte / 16], 1);
	write(STDOUT_FILENO, &hex_chars[byte % 16], 1);
}

static void	print_address(unsigned char *p)
{
	uintptr_t		addr;
	int				i;

	addr = (uintptr_t)p;
	i = (sizeof(uintptr_t) * CHAR_BIT) - CHAR_BIT;
	while (i >= 0)
	{
		print_hex_byte((unsigned char)((addr >> i) & 0xFF));
		i -= CHAR_BIT;
	}
	write(STDOUT_FILENO, ": ", 2);
}

static void	print_ascii_char(unsigned char c)
{
	if (c >= 32 && c <= 126)
		write(STDOUT_FILENO, &c, 1);
	else
		write(STDOUT_FILENO, ".", 1);
}

static void	debug_print_line(
	unsigned char *p, unsigned int i, unsigned int size)
{
	static const unsigned int	byte_per_line = 16;
	unsigned int				j;

	j = 0;
	while (j < byte_per_line)
	{
		if (i + j < size)
			print_hex_byte(p[i + j]);
		else
			write(STDOUT_FILENO, "  ", 2);
		if (j % 2 == 1)
			write(STDOUT_FILENO, " ", 1);
		j++;
	}
	write(STDOUT_FILENO, " ", 1);
	j = 0;
	while (j < byte_per_line)
	{
		if (i + j < size)
			print_ascii_char(p[i + j]);
		j++;
	}
}

void	*debug_print_memory(void *addr, unsigned int size)
{
	static const unsigned int	byte_per_line = 16;
	unsigned char				*p;
	unsigned int				i;

	if (!addr)
		return (NULL);
	p = (unsigned char *)addr;
	i = 0;
	while (i < size)
	{
		print_address(p + i);
		debug_print_line(p, i, size);
		write(STDOUT_FILENO, "\r\n", 2);
		i += byte_per_line;
	}
	return (addr);
}
