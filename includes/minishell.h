/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 14:12:05 by shonakam          #+#    #+#             */
/*   Updated: 2025/02/09 10:21:00 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <string.h>
# include <errno.h>
# include <stdbool.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <linux/limits.h>
# include "libft/libft.h"

# include "errors.h"
# include "token.h"
# include "parser.h"
# include "envlist.h"
# include "support.h"

# define READ	0
# define WRITE	1

extern volatile sig_atomic_t	g_signal_flag;

typedef struct s_minishell {
	char			*line;
	t_envlist		*envlist;
	t_token			**token;
	t_command		*cmd;
	int				hd_index;
	int				in_fd;
	int				status;
}				t_minishell;

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
	int		o_bkp;
	int		i_bkp;
}				t_rdir;

/*  <=== SIGNALHANDLER ===>  */
void		handle_signal(int sig);
void		setup_signals(void);
int			observe_signal(t_minishell *mini);

/*  <=== TOKENIZER ===>  */
t_token		*create_token(t_tokentype t, const char *l, size_t p, size_t s);
size_t		get_token_size(const char *line, size_t position);
void		extract_token(const char *line,
				t_token **toks, size_t pos, size_t c);
t_token		**ft_lexer(char *line);
char		*resolve_eos(char *line);

/*  <=== BUILTINS ===>  */
int			is_builtin(t_command *cmd);
int			builtin_runner(t_command *cmd, int fd, t_envlist *envlist);
int			cmd_cd(t_command *cmd, t_envlist *envlist);
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

/*  <=== EXECUTION ===>  */
int			resolve_script(t_command *cmd, t_minishell *mini);
int			is_last_arg_minishell(char *cmd);
int			exec_hd_support(t_command *cmd, t_minishell *m, int *p);
int			parse_exit_status(int status);
void		ft_exec_v6(t_minishell *mini);
int			get_exit_status(t_minishell *mini);

/*  <=== CLEANUP ===>  */
void		ft_clean(t_minishell *mini, int flag);
void		ft_clean_exit(t_minishell *mini);

#endif
