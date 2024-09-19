/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 09:09:41 by shonakam          #+#    #+#             */
/*   Updated: 2024/09/19 08:58:26 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

t_rdir	*init_redirect(void)
{
	t_rdir	*new;

	new = malloc(sizeof(t_rdir));
	if (!new)
		return (NULL);
	new->file = NULL;
	new->mode = -1;
	new->i_bkp = -1;
	new->o_bkp = -1;
	new->rdir_i = -1;
	new->rdir_o = -1;
	return (new);
}

int	get_redirect_mode(char *arg)
{
	int	mode;

	if (ft_strcmp(arg, ">>") == 0)
		mode =  O_CREAT | O_WRONLY | O_TRUNC;
	else if (ft_strcmp(arg, ">") == 0)
		mode = O_CREAT | O_WRONLY | O_APPEND;
	else if (ft_strcmp(arg, "<") == 0)
		mode = O_RDONLY;
	else
		mode = -1;
	return (mode);
}
