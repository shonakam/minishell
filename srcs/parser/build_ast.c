/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 05:55:24 by shonakam          #+#    #+#             */
/*   Updated: 2024/09/07 07:48:17 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static t_ast *create_node(TokenType type, char **argv)
{
	t_ast *node = (t_ast *)malloc(sizeof(t_ast));
	if (!node)
		return (NULL);
	node->type = type;
	node->argv = argv;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

static t_ast	*parse_command(t_token **token, int *index)
{
	int		size;
	int		argc;
	char	**argv;

	if (token[*index]->type != METACHAR_NONE)
		return (NULL);
	size = *index;
	while (size < count_tokens(token) && token[size]->type == METACHAR_NONE)
		size++;
	size = size - (*index);
	argv = (char **)malloc(sizeof(char *) * size + 1);
	if (!argv)
		return (NULL);
	argc = 0;
	printf(">>size=%d i=%d\n", size, (*index));
	printf(">> COPY START <<\n");
	while (--size > 0 && *index < count_tokens(token))
	{
		printf(">>%s\n", token[(*index)]->word);
		argv[argc++] = strdup(token[(*index)]->word);
		(*index) += 1;
	}
	argv[argc] = NULL;
	return (create_node(TOKEN_WORD, argv));
}

static t_ast *parse_pipeline(t_token **token, int *index)
{
	t_ast *left;
	t_ast *node;

	left = parse_command(token, index);
	while (token[*index]->type == METACHAR_PIPE)
	{
		(*index)++;
		node = create_node(METACHAR_PIPE, NULL);
		node->left = left;
		node->right = parse_command(token, index);
		left = node;
	}
	return (left);
}

static t_ast *parse_redirection(t_token **token, int *index, t_ast *left)
{
	t_ast	*node;
	char	**argv;

	// printf("--- HERE ---\n");
	while (token[*index]->type == METACHAR_OUTPUT_REDIRECT ||
			token[*index]->type == METACHAR_INPUT_REDIRECT ||
			token[*index]->type == METACHAR_APPEND_REDIRECT)
	{
		node = create_node(token[(*index)++]->type, NULL);
		if (!node)
			return (NULL);
		node->left = left;
		argv = (char **)malloc(2 * sizeof(char *));
		if (!argv)
			return (free(node), NULL);
		argv[0] = strdup(token[*index]->word);
		argv[1] = NULL;
		if (!argv[0])
			return (free(argv), free(node), NULL);
		node->right = create_node(TOKEN_WORD, argv);
		if (!node->right)
			return (free(argv[0]), free(argv), free(node), NULL);
		(*index)++;
		left = node;
	}
	return (left);
}

// まずパイプラインをパース
// 次にリダイレクトがあればそれを処理
t_ast	*build_ast(t_token **token, int *index)
{
	t_ast	*pipeline_ast;

	pipeline_ast = parse_pipeline(token, index);
	if (!pipeline_ast)
		return (NULL);
	pipeline_ast = parse_redirection(token, index, pipeline_ast);
	return (pipeline_ast);
}
