#ifndef AST_H
# define AST_H

typedef struct s_ast_node {
    enum { NODE_COMMAND, NODE_PIPELINE } nodetype;
    char				**args;  // コマンドの引数
    struct s_ast_node	*left;
    struct s_ast_node	*right;
}				t_ast_node;

t_ast_node *parse_pipeline(t_token **tokens);

#endif
