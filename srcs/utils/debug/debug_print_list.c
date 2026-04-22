#include "../utils_internal.h"

void	debug_print_list(t_list *list, void (*f)(void *))
{
	if (!list)
	{
		printf("(empty list)\r\n");
		return ;
	}
	printf("--- List Debug Start ---\r\n");
	while (list)
	{
		f(list->content);
		list = list->next;
	}
	printf("--- List Debug End ---\r\n");
}
