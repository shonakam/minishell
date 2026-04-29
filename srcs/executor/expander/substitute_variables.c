#include "../executor_internal.h"

static size_t	get_var_len(char *str)
{
	size_t	len;

	len = 0;
	if (str[0] == '?')
		return (1);
	while (str[len] && (ft_isalnum(str[len]) || str[len] == '_'))
		len++;
	return (len);
}

static char	*get_expanded_val(t_context *ctx, char *str, size_t len)
{
	char	*name;
	char	*val;
	t_env	*node;

	if (len == 0)
		return (x_strdup("$"));
	if (str[0] == '?')
		return (ft_itoa(ctx->last_status));
	name = ft_substr(str, 0, len);
	node = env_find(ctx->env_list, name);
	free(name);
	if (node && node->has_value)
		val = x_strdup(node->value);
	else
		val = x_strdup("");
	return (val);
}

static char	*extract_and_join_var(
	t_context *ctx, char *str, size_t *i, char *res)
{
	size_t	len;
	char	*val;
	char	*joined;

	len = get_var_len(&str[*i + 1]);
	val = get_expanded_val(ctx, &str[*i + 1], len);
	joined = ft_strjoin(res, val);
	free(res);
	free(val);
	if (len == 0)
		*i += 1;
	else
		*i += len + 1;
	return (joined);
}

char	*substitute_variables(t_context *ctx, char *str)
{
	char	*new_str;
	size_t	i;

	new_str = x_strdup("");
	i = 0;
	while (str && str[i])
	{
		if (str[i] == '$' && str[i + 1])
			new_str = extract_and_join_var(ctx, str, &i, new_str);
		else
			new_str = append_char(new_str, str[i++]);
	}
	return (new_str);
}
