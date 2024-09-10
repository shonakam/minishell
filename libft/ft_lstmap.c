/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosh <mosh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 17:06:21 by kmoshker          #+#    #+#             */
/*   Updated: 2024/04/21 23:10:06 by mosh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// t_list	*ft_lstmap(t_list *lst, void *(*f)(int), void (*del)(int))
// {
// 	t_list	*new;
// 	t_list	*tmp;

// 	new = NULL;
// 	if (!lst || !f)
// 		return (new);
// 	while (lst)
// 	{
// 		tmp = ft_lstnew((int)(*f)(lst->content));
// 		if (!tmp)
// 		{
// 			ft_lstclear(&new, (*del));
// 			return (NULL);
// 		}
// 		ft_lstadd_back(&new, tmp);
// 		lst = lst->next;
// 	}
// 	return (new);
// }
