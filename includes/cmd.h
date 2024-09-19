/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 18:40:06 by shonakam          #+#    #+#             */
/*   Updated: 2024/09/19 10:46:38 by shonakam         ###   ########.fr       */
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

typedef struct s_rdir {
	char	*file;
	int		mode;
	int		rdir_i;
	int		rdir_o;
	// int		rdir_fd;
	int		o_bkp;
	int		i_bkp;
}				t_rdir;

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
int			handle_heredoc(t_command *cmd, int *index, int s, t_envlist *e);

/*  <=== REDIRECTION ===>  */
t_rdir		*init_redirect(void);
void		parse_redirects(t_command *cmd, t_rdir *info);
void		apply_redirects(t_rdir *info);
char		**prepare_exec_argv(char **argv, int *argc);
void		set_bkp_fd(t_rdir *info);
void		restore_io(t_rdir *info);

int			get_redirect_mode(char *arg);

/*  <=== EXPASION ===>  */
void		init_expand_state(t_state *state);
char		*expand_variables(const char *input, int status, t_envlist *e);
char		*expand_special_variable(const char *str, int status);
char		*remove_quotes(const char *input);
void		state_toggle(t_state *state, int flag);
int			exec_handler(t_command *c, t_minishell *m, int *p, t_rdir *i);
void		exec_bin(t_command *cmd, int *p, t_minishell *mini);

#endif