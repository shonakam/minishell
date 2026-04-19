#include "../utils_internal.h"

void	debug_print_list(t_list *list, void (*f)(void *))
{
	if (!list)
	{
		printf("(empty list)\n");
		return ;
	}
	printf("--- List Debug Start ---\n");
	while (list)
	{
		f(list->content);
		list = list->next;
	}
	printf("--- List Debug End ---\n");
}
