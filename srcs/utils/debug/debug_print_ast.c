#include "../utils_internal.h"

static void debug_print_ast_recursive(t_ast_node *node, int depth)
{
	if (!node)
		return ;
	for (int i = 0; i < depth; i++)
		printf("  ");

	static const char *node_names[] = {
		[NODE_COMMAND] = "COMMAND",
		[NODE_PIPELINE] = "PIPELINE",
		[NODE_AND] = "AND",
		[NODE_OR] = "OR",
		[NODE_SEMICOLON] = "SEMICOLON",
		[NODE_BACKGROUND] = "BACKGROUND",
		[NODE_SUBSHELL] = "SUBSHELL"
	};

	printf("|- %s", node_names[node->type]);

	if (node->type == NODE_COMMAND && node->data.command)
	{
		t_simple_command	*cmd = node->data.command;
		t_list				*curr = cmd->args;

		printf(": [");
		while (curr)
		{
			// contentをt_arg型として扱い、文字列を取り出す
			t_arg *arg = (t_arg *)curr->content;
			printf("%s", arg->str);
			
			// 次のノードがある場合だけカンマを打つ
			if (curr->next)
				printf(", ");
			curr = curr->next;
		}
		printf("]");
		if (cmd->redirects)
			printf(" (has redirects)");
	}
	printf("\n");

	debug_print_ast_recursive(node->left, depth + 1);
	debug_print_ast_recursive(node->right, depth + 1);
}

void	debug_print_ast(t_ast_node *ast)
{
	printf("\033[34m--- AST Debug Start ---\033[0m\n"); // 青色で見やすく
	if (!ast)
		printf("(empty tree)\n");
	else
		debug_print_ast_recursive(ast, 0);
	printf("\033[34m--- AST Debug End ---\033[0m\n");
}
