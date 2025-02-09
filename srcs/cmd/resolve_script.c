/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolve_script.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 09:43:10 by shonakam          #+#    #+#             */
/*   Updated: 2025/02/09 10:13:29 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static char	*get_shell_path(t_minishell *mini)
{
	char	*path;

	path = get_bin_path(mini->envlist, "sh");
	if (!path)
	{
		perror("minishell: sh not found");
		exit(EXIT_FAILURE);
	}
	return (path);
}

static char	*get_executable_path(t_minishell *mini, char *cmd)
{
	char	*path;

	if (cmd[0] == '/' || (cmd[0] == '.' && (cmd[1] == '/' || cmd[1] == '.')))
	{
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
		print_error("command not found", cmd);
		exit(EXIT_FAILURE);
	}
	path = get_bin_path(mini->envlist, cmd);
	if (!path)
	{
		print_error("command not found", cmd);
		exit(EXIT_FAILURE);
	}
	return (path);
}

static char	**prepare_script_args(char *sh_path,
	char *bin_path, char **cmd_argv)
{
	int		i;
	int		argc;
	char	**sh_argv;

	i = 0;
	argc = ft_strarr_size(cmd_argv);
	sh_argv = malloc((argc + 2) * sizeof(char *));
	if (!sh_argv)
	{
		perror("minishell");
		exit(EXIT_FAILURE);
	}
	sh_argv[0] = sh_path;
	sh_argv[1] = bin_path;
	while (cmd_argv[i + 1])
	{
		sh_argv[i + 2] = cmd_argv[i + 1];
		i++;
	}
	sh_argv[i + 2] = NULL;
	return (sh_argv);
}

int	resolve_script(t_command *cmd, t_minishell *mini)
{
	char	*sh_path;
	char	*bin_path;
	char	**argv;
	char	**envp;

	sh_path = get_shell_path(mini);
	bin_path = get_executable_path(mini, cmd->argv[0]);
	argv = prepare_script_args(sh_path, bin_path, argv);
	if (!argv)
		return (perror("minishell"), exit(EXIT_FAILURE), -1);
	envp = convert_to_envp(&mini->envlist);
	execve(sh_path, argv, envp);
	perror("minishell");
	exit(EXIT_FAILURE);
}
