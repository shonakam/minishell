/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 22:25:51 by shonakam          #+#    #+#             */
/*   Updated: 2025/02/19 16:04:01 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static int	check_syntax(t_token **tokens)
{
	int	status;

	status = valid_unsupported_tokens(tokens);
	if (status == SYNTAX_ERRNO)
		return (status);
	status = valid_context(tokens);
	if (status == SYNTAX_ERRNO)
		return (status);
	return (0);
}

t_token	**ft_lexer(char *line, t_minishell *mini)
{
	t_token	**tokens;

	add_history(line);
	if (!valid_quote(line))
	{
		print_syntax_error("\' or \"");
		mini->status = SYNTAX_ERRNO;
		return (NULL);
	}
	if (strlen(line) > 0)
		rl_replace_line(line, 1);
	tokens = (t_token **)malloc(ARGUMENT_SIZE * sizeof(t_token *));
	if (!tokens)
		return (print_syscall_error("malloc", ENOMEM), NULL);
	tokenizer(tokens, line, 0, 0);
	mini->status = check_syntax(tokens);
	if (mini->status == SYNTAX_ERRNO)
		return (free(mini->line), free_tokens(tokens), NULL);
	return (tokens);
}
