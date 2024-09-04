/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 00:52:47 by mosh              #+#    #+#             */
/*   Updated: 2024/08/31 16:07:53 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"
#include "includes/ast.h"

int count_tokens(t_token **tokens)
{
    int count = 0;
    while (tokens[count] != NULL)
	{
        count++;
    }
    return count;
}

char **extract_args(t_token **tokens)
{
	int		count;
	char	**args;
	int		i;
	
	count = count_tokens(tokens);
	args = malloc(sizeof(char*) * (count + 1));
	i = 0;
	while (i < count)
	{
		args[i] = strdup(tokens[i]->word);
		i++;
	}
	args[count] = NULL;
	return (args);
}
t_ast_node *parse_command(t_token **tokens)
{
	t_ast_node	*node;

	node = malloc(sizeof (t_ast_node));
	if (!node)
		return NULL;
	node->nodetype = NODE_COMMAND;
	node->args = extract_args(tokens);
	node->left = node->right = NULL;
	return (node);
}

t_ast_node *parse_pipeline(t_token **tokens)
{
	t_ast_node	*right;
	t_ast_node	*pipe_node;
	t_ast_node	*left;

	left = parse_command(tokens);
	while (*tokens && (*tokens)->type == METACHAR_PIPE)
	{
		tokens++;  // パイプトークンをスキップ
		right = parse_command(tokens);
		pipe_node = malloc(sizeof (t_ast_node));
		pipe_node->nodetype = NODE_PIPELINE;
		pipe_node->left = left;
		pipe_node->right = right;
		left = pipe_node;
	}
	return left;
}