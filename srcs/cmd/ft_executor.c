/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_executor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 08:21:18 by shonakam          #+#    #+#             */
/*   Updated: 2025/02/03 01:02:56 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

/* "source ." はサポートしない */
static void	handle_dot_command(t_command *cmd, t_minishell *mini)
{
	if (ft_strcmp(cmd->argv[0], ".") == 0)
	{
		ft_putendl_fd("minishell: .: filename argument required", 2);
		ft_putendl_fd(".: usage: . filename [arguments]", 2);
		ft_putendl_fd("\033[31m but not supported\033[0m", 2);
		exit(2);
	}
}

/* シェルスクリプトを実行 */
static int	resolve_script(t_command *cmd, t_minishell *mini)
{
	char	*path = get_bin_path(mini->envlist, "sh");
	char	**sh_argv;
	int		i;

	if (!path)
		return (perror("minishell"), exit(EXIT_FAILURE), -1);
	sh_argv = malloc((ft_strarr_size(cmd->argv) + 2) * sizeof(char *));
	if (!sh_argv)
		return (perror("minishell"), exit(EXIT_FAILURE), -1);
	sh_argv[0] = path;
	sh_argv[1] = cmd->argv[0];
	i = 0;
	while (cmd->argv[i + 1])
	{
		sh_argv[i + 2] = cmd->argv[i + 1];
		i++;
	}
	sh_argv[i + 2] = NULL;

	execve(path, sh_argv, convert_to_envp(&mini->envlist));
	perror("minishell");
	exit(EXIT_FAILURE);
}

/* バイナリコマンドの実行 */
static void	execute_binary(t_command *cmd, int *p, t_minishell *mini)
{
	char	*path;
	int		exec_flag;

	if (mini->in_fd != STDIN_FILENO)
		redirect_fd(mini->in_fd, STDIN_FILENO);
	if (p && cmd->next)
	{
		close(p[READ]);
		redirect_fd(p[WRITE], STDOUT_FILENO);
	}

	handle_dot_command(cmd, mini);
	path = get_bin_path(mini->envlist, cmd->argv[0]);
	exec_flag = is_cmd(cmd->argv[0]);
	mini->status = handle_exec_errors(path, p, exec_flag);
	if (mini->status != 0)
		exit(mini->status);
	if (exec_flag == 0)
		exit(resolve_script(cmd, mini));

	execve(path, cmd->argv, convert_to_envp(&mini->envlist));
	perror("minishell");
	exit(EXIT_FAILURE);
}

/* バイナリコマンドを fork して実行 */
void	exec_bin(t_command *cmd, int *p, t_minishell *mini)
{
	pid_t	pid = fork();

	if (pid == 0)
		execute_binary(cmd, p, mini);
	else
	{
		if (cmd->next)
			close(p[WRITE]);
		if (mini->in_fd != STDIN_FILENO)
			close(mini->in_fd);
	}
	g_signal_flag = (sig_atomic_t)pid;
	mini->status = parse_exit_status(mini->status);
	g_signal_flag = 0;
}

/* コマンドを実行 */
void	ft_exec_v6(t_minishell *mini)
{
	t_command	*cmd = mini->cmd;
	int			p[2];
	t_rdir		*info;

	while (cmd)
	{
		info = init_redirect();
		parse_redirects(cmd, info);
		if (info->rdir_i == INT_MIN)
		{
			mini->status = 1;
			free(info);
			break;
		}
		exec_handler(cmd, mini, p, info);
		free(info);
		cmd = cmd->next;
	}
	while (waitpid(-1, &mini->status, 0) > 0)
		;
	mini->status = parse_exit_status(mini->status);
}
