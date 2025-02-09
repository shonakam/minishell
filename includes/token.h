/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 14:12:20 by shonakam          #+#    #+#             */
/*   Updated: 2025/02/08 20:34:50 by shonakam         ###   ########.fr       */
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
	METACHAR_SINGLE_QUOTE,
	METACHAR_DOUBLE_QUOTE,
	METACHAR_DOLLAR,		
	METACHAR_ENV_VAR,
	TOKEN_WORD,
}			t_tokentype;

typedef struct s_token {
	t_tokentype		type;
	char			*word;
}				t_token;

t_token	**check_unexpected_token(t_token **t);

#endif
