/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 22:25:51 by shonakam          #+#    #+#             */
/*   Updated: 2025/02/12 22:02:26 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

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
	if (validate_tokens(tokens))
	{
		mini->status = SYNTAX_ERRNO;
		return (NULL);
	}
	return (tokens);
}
