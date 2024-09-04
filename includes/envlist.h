/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envlist.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 16:19:07 by shonakam          #+#    #+#             */
/*   Updated: 2024/09/04 18:56:38 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVLIST_H
# define ENVLIST_H

typedef struct s_envlist {
	char				*key;
	char				*value;
	struct s_envlist	*next;
}				t_envlist;

t_envlist	*make_envlist(char **envp);
void	ft_putenv(t_envlist **l, const char *k, const char *v);

#endif