#include "builtin_internal.h"

static void print_declare(t_env *env)
{
	ft_printf("declare -x %s", env->key);
	if (env->has_value)
		ft_printf("=\"%s\"", env->value);
	ft_printf("\n");
}

static int	compare_env(void *a, void *b)
{
	t_env	*env_a;
	t_env	*env_b;
	size_t	len_a;
	size_t	len_b;

	env_a = (t_env *)((t_list *)a)->content;
	env_b = (t_env *)((t_list *)b)->content;
	len_a = ft_strlen(env_a->key);
	len_b = ft_strlen(env_b->key);
	if (len_a > len_b)
		return (ft_strncmp(env_a->key, env_b->key, len_a));
	return (ft_strncmp(env_a->key, env_b->key, len_b));
}

static void	sort_env_array(t_list **array, size_t size)
{
	size_t	i;
	size_t	j;
	t_list	*tmp;

	i = 0;
	while (i < size - 1)
	{
		j = i + 1;
		while (j < size)
		{
			if (compare_env(array[i], array[j]) > 0)
			{
				tmp = array[i];
				array[i] = array[j];
				array[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

/* Check NULL node */
void	print_sorted_export(t_context *ctx)
{
	t_list	**array;
	t_list	*curr;
	size_t	size;
	size_t	i;

	size = ft_lstsize(ctx->env_list);
	if (size <= 1)
		return ;
	array = x_calloc(size - 1, sizeof(t_list *));
	curr = ctx->env_list->next;
	i = 0;
	while (curr)
	{
		array[i++] = curr;
		curr = curr->next;
	}
	sort_env_array(array, size - 1);
	i = 0;
	while (i < size - 1)
		print_declare((t_env *)array[i++]->content);
	free(array);
}
