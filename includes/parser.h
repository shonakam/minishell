#ifndef PARSER_H
# define PARSER_H

# include <stdbool.h>
# include "../libft/libft.h"
# include "lexer.h"

struct s_context;
typedef struct s_context t_context;

typedef enum e_node_type
{
	NODE_PIPELINE,
	NODE_AND,
	NODE_OR,
	NODE_SEMICOLON,
	NODE_BACKGROUND,
	NODE_SUBSHELL,
	NODE_COMMAND,
	NODE_SIZE
}	t_node_type;

typedef enum e_redir_type
{
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	REDIR_HEREDOC
}	t_redir_type;

typedef struct s_pipeline t_pipeline;
typedef struct s_subshell t_subshell;
typedef struct s_simple_command t_simple_command;

typedef union u_node_data {
	t_pipeline			*pipeline;
	t_subshell			*subshell;
	t_simple_command	*command;
}	t_node_data;

typedef struct s_subshell
{
	struct s_ast_node	*inner_ast;
	t_list				*redirects;
}   t_subshell;

/*
 * 'data' is kept as a value (not a pointer) for the following reasons:
 * 1. Memory Efficiency: Reduces malloc overhead and avoids memory fragmentation.
 * 2. Cache Locality: Keeping data adjacent to the node type improves CPU cache hits.
 * 3. Lifecycle Management: Simplifies memory cleanup as 'data' is freed
 * automatically when the node itself is freed.
 */
typedef struct s_ast_node
{
	t_node_type			type;
	struct s_ast_node	*left;
	struct s_ast_node	*right;
	t_node_data			data;
	bool				is_background;
}	t_ast_node;

typedef struct s_pipeline
{
	t_list	*simple_commands;
}	t_pipeline;

typedef struct s_arg {
	char		*str; // Command + Arguments
	t_qstate	state;
}	t_arg;

typedef struct s_simple_command
{
	t_list	*args;
	t_list	*redirects; // Redirections
}	t_simple_command;

typedef struct s_redirect
{
	t_redir_type	type;
	char			*target;     /* Filename or heredoc delimiter */
	char            *tmp_filename;
	int				fd;          /* Target file descriptor (e.g., 2 for 2>), defaults to -1 */
	bool			need_expand; /* True if heredoc content requires expansion */
}	t_redirect;

t_ast_node	*parser(t_context *ctx, t_list **tokens);
void		ast_node_free(t_ast_node *node);
t_arg		*arg_new(char *str, t_qstate state);
void		arg_free(void *content);

#endif /* PARSER_H */
