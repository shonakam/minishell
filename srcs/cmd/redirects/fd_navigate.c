/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_navigate.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 22:02:02 by shonakam          #+#    #+#             */
/*   Updated: 2025/02/19 23:42:33 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static void	redirect_fd(int src_fd, int dest_fd)
{
	if (src_fd != dest_fd)
	{
		if (dup2(src_fd, dest_fd) == -1)
		{
			print_syscall_error("dup2: redirect_fd", 0);
			exit(EXIT_FAILURE);
		}
		close(src_fd);
	}
}


static void	set_in(t_rdir *i, t_command *c, int *p, t_minishell *m)
{
	(void)c;
	(void)p;
	if (m->in_fd != STDIN_FILENO)
	{
		redirect_fd(m->in_fd, STDIN_FILENO);
		i->i_bkp = m->in_fd;
	}
	if (check_fd(i->rdir_i))
	{
		redirect_fd(i->rdir_i, STDIN_FILENO);
		i->i_bkp = i->rdir_i;
	}
}

static void	set_out(t_rdir *i, t_command *c, int *p, t_minishell *m)
{
	(void)m;
	if (c->next && !check_fd(i->rdir_o))
	{
		close(p[READ]);
		redirect_fd(p[WRITE], STDOUT_FILENO);
		i->o_bkp = p[WRITE];
	}
	else if (check_fd(i->rdir_o))
	{
		redirect_fd(i->rdir_o, STDOUT_FILENO);
		i->o_bkp = i->rdir_o;
	}
}

void	fd_navigate(t_rdir *i, t_command *c, int *p, t_minishell *m)
{
	dprintf(STDERR_FILENO, "[setup_child_fds] in_fd: %d, rdir_i: %d, rdir_o: %d\n",
			m->in_fd, i->rdir_i, i->rdir_o);
	set_in(i, c, p, m);
	set_out(i, c, p, m);
}
