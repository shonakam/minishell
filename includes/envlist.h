/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 16:19:07 by shonakam          #+#    #+#             */
/*   Updated: 2024/08/31 16:24:21 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVLIST_H
# define ENVLIST_H

typedef struct s_envlist {
	char		*key;
	char		*value;
	t_envlist	*next;
}				t_envlist;

#endif