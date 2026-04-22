#include "../utils_internal.h"

void	debug_print_job(t_context *ctx)
{
	t_job	*curr;
	size_t	i;

	if (!ctx)
		return ;
	ft_printf("\n--- 🛠 Job Control Debug Start ---\n");
	ft_printf("Next ID to assign: %zd\n", ctx->job.next_id);
	
	curr = ctx->job.head;
	if (!curr)
	{
		ft_printf("Status: (No active jobs in list)\n");
	}
	while (curr)
	{
		ft_printf("[%zd] %s | %s | Count: %zu / Cap: %zu\n",
			curr->job_id,
			curr->is_background ? "BACK" : "FORE",
			curr->cmd_line ? curr->cmd_line : "(NULL)",
			curr->count,
			curr->capacity);
		ft_printf("  PIDs: ");
		if (!curr->pids)
		{
			ft_printf("(NULL pointer!)");
		}
		else
		{
			i = 0;
			while (i < curr->count)
			{
				ft_printf("%d ", (int)curr->pids[i]);
				i++;
			}
		}
		ft_printf("\n");
		curr = curr->next;
	}
	ft_printf("--- Job Control Debug End ---\n\n");
}
