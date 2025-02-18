/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 09:09:19 by shonakam          #+#    #+#             */
/*   Updated: 2025/02/13 09:18:21 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

/* https://www.gnu.org/software/bash/manual/html_node/Exit-Status.html */
void	print_syntax_error(const char *token)
{
	char	*prefix;
	char	*cause;
	char	*msg;

	prefix = "minishell: syntax error near unexpected token `";
	cause = ft_strjoin(token, "\'");
	if (!cause)
	{
		print_syscall_error("malloc: print_syntax_error", ENOMEM);
		return ;
	}
	msg = ft_strjoin(prefix, cause);
	if (!msg)
	{
		print_syscall_error("malloc: print_syntax_error", ENOMEM);
		free(cause);
		return ;
	}
	ft_putendl_fd(msg, STDERR_FILENO);
	free(cause);
	free(msg);
}

void	print_exec_error(
	const char *cmd, const char *pattern, int code, t_minishell *mini)
{
	char	*prefix;
	char	*cause;
	char	*msg;

	prefix = "minishell: ";
	cause = ft_strjoin(cmd, pattern);
	if (!cause)
	{
		print_syscall_error("malloc: print_exec_error", ENOMEM);
		return ;
	}
	msg = ft_strjoin(prefix, cause);
	if (!msg)
	{
		print_syscall_error("malloc: print_exec_error", ENOMEM);
		free(cause);
		return ;
	}
	ft_putendl_fd(msg, STDERR_FILENO);
	if (mini)
		mini->status = code;
	free(cause);
	free(msg);
}

void	print_permission_error(const char *target, t_minishell *mini)
{
	char	*prefix;
	char	*cause;
	char	*msg;

	prefix = "minishell: ";
	cause = ft_strjoin(target, ": Permission denied");
	if (!cause)
	{
		print_syscall_error("mallo: print_permission_error", ENOMEM);
		return ;
	}
	msg = ft_strjoin(prefix, cause);
	if (!msg)
	{
		print_syscall_error("malloc: print_permission_error", ENOMEM);
		free(cause);
		return ;
	}
	ft_putendl_fd(msg, STDERR_FILENO);
	mini->status = 126;
	free(cause);
	free(msg);
}

void	print_heredoc_error(const char *delimiter)
{
	char	*prefix;
	char	*cause;
	char	*msg;

	prefix = "warning: here-document delimited by end-of-file (wanted `";
	cause = ft_strjoin(delimiter, "\')");
	if (!cause)
	{
		print_syscall_error("malloc: print_heredoc_error", ENOMEM);
		return ;
	}
	msg = ft_strjoin(prefix, cause);
	if (!msg)
	{
		print_syscall_error("malloc: print_heredoc_error", ENOMEM);
		free(cause);
		return ;
	}
	ft_putendl_fd(msg, STDERR_FILENO);
	free(cause);
	free(msg);
}

void	print_syscall_error(const char *msg, const int e)
{
	if (e)
		errno = e;
	perror(msg);
	errno = 0;
}
