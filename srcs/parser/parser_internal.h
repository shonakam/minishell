#ifndef PARSER_INTERNAL_H
# define PARSER_INTERNAL_H

# include "error.h"
# include "parser.h"

typedef bool (*t_token_rule)(t_token_type);
bool		is_ok_command(t_token_type type);
bool		is_ok_pipeline(t_token_type type);
bool		is_ok_list(t_token_type type);
bool		is_next_token_valid(
	t_context *ctx, t_list **tokens, t_token_rule is_ok);

void		parser_syntax_error(t_context *ctx, char *token);

t_ast_node	*parse_list(t_context *ctx, t_list **tokens);
t_ast_node	*parse_pipeline(t_context *ctx, t_list **tokens);
t_ast_node	*parse_command(t_context *ctx, t_list **tokens);
t_ast_node	*parse_subshell(t_context *ctx, t_list **tokens);

t_token			*token_peek(t_list **tokens);
t_token_type	token_peek_type(t_list **tokens);
t_token			*token_consume(t_list **tokens);

t_ast_node	*ast_node_new(t_node_type type);
void		ast_node_free(t_ast_node *node);
t_ast_node	*ast_node_attach(
	t_node_type type, t_ast_node *left, t_ast_node *right);

t_pipeline	*pipeline_new(void);
void		pipeline_free(t_pipeline *pipeline);

t_simple_command	*simple_command_new(void);
void				simple_command_free(void *content);

t_redirect	*redirect_new(t_redir_type type, char *target);
void		redirect_free(void *content);

t_subshell	*subshell_new(t_ast_node *inner_ast);
void		subshell_free(t_subshell *sub);

bool		is_token_redirect(t_token *token);
bool		is_token_word(t_token *token);
bool		is_command_element(t_token *token);
bool		is_list_operator(t_token *token);
bool		is_logical_operator(t_token *token);

bool		is_empty_command(t_simple_command *cmd);
bool		parse_redirect_into_cmd(t_simple_command *cmd, t_list **tokens);
bool		parse_arg_into_cmd(t_simple_command *cmd, t_list **tokens);

char		**expand_args_array(char **args, char *new_arg);

#endif /* PARSER_INTERNAL_H */
