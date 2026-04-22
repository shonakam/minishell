#include "parser_internal.h"

static bool	append_command_element(
	t_context *ctx, t_simple_command *cmd, t_list **tokens)
{
	if (apply_parser_rule(is_io, *tokens))
		return (parse_redirect_into_cmd(ctx, cmd, tokens));
	if (apply_parser_rule(is_word, *tokens))
		return (parse_arg_into_cmd(cmd, tokens));
	return (false);
}

t_ast_node	*parse_command(t_context *ctx, t_list **tokens)
{
	t_simple_command	*cmd;
	t_ast_node			*node;

	if (apply_parser_rule(is_subshell_start, *tokens))
		return (parse_subshell(ctx, tokens));
	cmd = simple_command_new();
	if (!cmd)
		return (NULL);
	while (apply_parser_rule(is_simple_command_element, *tokens))
	{
		if (!append_command_element(ctx, cmd, tokens))
			return (simple_command_free(cmd), NULL);
	}
	if (simple_command_is_empty(cmd))
		return (simple_command_free(cmd), NULL);
	node = ast_node_new(get_current_node_type(*tokens));
	if (!node)
		return (simple_command_free(cmd), NULL);
	node->data.command = cmd;
	return (node);
}
