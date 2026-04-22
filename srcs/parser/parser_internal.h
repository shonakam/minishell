#ifndef PARSER_INTERNAL_H
# define PARSER_INTERNAL_H

# include "error.h"
# include "utils.h"
# include "session.h"
# include "lexer.h"
# include "parser.h"

/* validator section */
typedef bool (*t_token_rule)(t_token_type);
bool	apply_parser_rule(const t_token_rule rule, t_list *tokens);
bool	is_ok_background(t_token_type type);
bool	is_ok_list(t_token_type type);
bool	is_ok_pipeline(t_token_type type);
bool	is_ok_command(t_token_type type);
bool	is_delimiter(t_token_type type);
bool	is_command_start(t_token_type type);
bool	is_simple_command_element(t_token_type type);
bool	is_pipe_op(t_token_type type);
bool	is_logical_op(t_token_type type);
bool	is_list_op(t_token_type type);
bool	is_control_op(t_token_type type);
bool	is_word(t_token_type type);
bool	is_subshell_start(t_token_type type);
bool	is_subshell_end(t_token_type type);
bool	is_io(t_token_type type);
bool	is_eof(t_token_type type);

void	parser_syntax_error(t_context *ctx, char *token);

bool	is_unexpected_at_start(t_context *ctx, t_list **tokens);
bool	is_unexpected_at_end(t_context *ctx, t_list **tokens);
bool	is_unexpected_at_contextual(
	t_context *ctx, t_list **tokens, t_token_rule is_ok);

t_node_type		get_node_type(t_token_type type);
t_node_type		get_current_node_type(t_list *tokens);
t_redir_type	get_redir_type(t_token_type type);
t_redir_type	get_current_redir_type(t_list *tokens);

t_ast_node	*parse_list(t_context *ctx, t_list **tokens);
t_ast_node	*parse_logical(t_context *ctx, t_list **tokens);
t_ast_node	*parse_pipeline(t_context *ctx, t_list **tokens);
t_ast_node	*parse_command(t_context *ctx, t_list **tokens);
t_ast_node	*parse_subshell(t_context *ctx, t_list **tokens);

t_subshell	*subshell_new(t_ast_node *inner_ast);
void		subshell_free(t_subshell *sub);


bool		parse_redirect_into_cmd(t_simple_command *cmd, t_list **tokens);
bool		parse_arg_into_cmd(t_simple_command *cmd, t_list **tokens);
void		set_heredoc_delimiter(t_redirect *redir, t_token *token);

#endif /* PARSER_INTERNAL_H */
