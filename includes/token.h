/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 14:12:20 by shonakam          #+#    #+#             */
/*   Updated: 2025/02/14 19:37:12 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# ifndef ARGUMENT_SIZE
#  define ARGUMENT_SIZE 1024
# endif

typedef enum e_tokentype {
	METACHAR_NONE,
	METACHAR_PIPE,
	METACHAR_INPUT_REDIRECT,
	METACHAR_OUTPUT_REDIRECT,
	METACHAR_APPEND_REDIRECT,
	METACHAR_HEREDOC,
	METACHAR_AND,
	METACHAR_SINGLE_QUOTE,
	METACHAR_DOUBLE_QUOTE,
	METACHAR_DOLLAR,
}			t_tokentype;

typedef struct s_token {
	t_tokentype		type;
	char			*word;
}				t_token;

int			is_metachar(t_tokentype t);
int			is_pipe_or_and(t_tokentype t);
int			is_redirects(t_tokentype t);
int			valid_unsupported_tokens(t_token **tokens);
int			valid_context(t_token **tokens);
void		tokenizer(t_token **toks, char *line, size_t pos, size_t index);

#endif
