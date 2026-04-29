#include "parser_internal.h"

static bool	append_subshell_redirects(
	t_context *ctx, t_ast_node *node, t_list **tokens)
{
	while (apply_parser_rule(is_io, *tokens))
	{
		if (!parse_redirect_into_node(ctx, node, tokens))
			return (false);
	}
	return (true);
}

static t_ast_node	*parse_subshell_node(t_context *ctx, t_list **tokens)
{
	t_ast_node	*node;

	node = parse_subshell(ctx, tokens);
	if (!node)
		return (NULL);
	if (!append_subshell_redirects(ctx, node, tokens))
		return (ast_node_free(node), NULL);
	return (node);
}

static bool	append_command_element(
	t_context *ctx, t_simple_command *cmd, t_list **tokens)
{
	if (apply_parser_rule(is_io, *tokens))
		return (parse_redirect_into_cmd(ctx, cmd, tokens));
	if (apply_parser_rule(is_word, *tokens))
		return (parse_arg_into_cmd(cmd, tokens));
	return (false);
}

static t_ast_node	*parse_simple_cmd_node(t_context *ctx, t_list **tokens)
{
	t_simple_command	*cmd;
	t_ast_node			*node;

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
	node = ast_node_new(NODE_COMMAND);
	if (node)
		node->data.command = cmd;
	else
		simple_command_free(cmd);
	return (node);
}

t_ast_node	*parse_command(t_context *ctx, t_list **tokens)
{
	if (apply_parser_rule(is_subshell_start, *tokens))
		return (parse_subshell_node(ctx, tokens));
	return (parse_simple_cmd_node(ctx, tokens));
}
