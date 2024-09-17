/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 18:40:06 by shonakam          #+#    #+#             */
/*   Updated: 2024/09/18 00:36:19 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CMD_H
# define FT_CMD_H

typedef struct s_state {
	char		*result;
	char		*v;
	size_t		s;
	size_t		e;
	size_t		in_single;
	size_t		in_double;
}				t_state;

/*  <=== BUILTINS ===>  */
int			is_builtin(t_command *cmd);
int			builtin_runner(t_command *cmd, int fd, t_envlist *envlist);
int			cmd_cd(t_command *cmd);
int			cmd_echo(t_command *cmd, int fd);
int			cmd_env(int fd, t_envlist *envlist);
int			cmd_exit(t_command *cmd);
int			cmd_export(t_command *cmd, int fd, t_envlist *envlist);
int			cmd_pwd(t_command *cmd, int fd);
int			cmd_unset(t_command *cmd, t_envlist *envlist);

/*  <=== HEREDOCUMENTS ===>  */
t_command	*build_commands(t_token **tokens, int count);
int			handle_heredoc(t_command *cmd, int *index, t_envlist *e);

/*  <=== EXPASION ===>  */
void		init_expand_state(t_state *state);
char		*extract_env_variable(const char *str);
char		*expand_special_variable(const char *str, int status);
char		*expand_env_variable(const char *str, t_envlist *envlist, int *i);
// char		*expand_variables(const char *str, t_envlist *envlist);
char		*process_quotes(const char *str, t_envlist *envlist);
void		state_toggle(t_state *state, int flag);

#endif