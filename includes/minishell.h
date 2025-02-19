/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 14:12:05 by shonakam          #+#    #+#             */
/*   Updated: 2025/02/19 14:56:46 by shonakam         ###   ########.fr       */
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
# include <sys/ioctl.h>
# include <termios.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"

# if defined(__linux__)
# if defined(__UBUNTU__) || defined(__DEBIAN__) || defined(__gnu_linux__)
# include <linux/limits.h>
# else
# include <limits.h>
# endif
# elif defined(__APPLE__)
# include <sys/syslimits.h>
# endif

# include "command.h"
# include "util.h"
# include "envlist.h"
# include "token.h"

# define READ	0
# define WRITE	1
# define SYNTAX_ERRNO	2

extern volatile sig_atomic_t	g_signal_flag;

typedef struct s_minishell {
	char			*line;
	t_envlist		*envlist;
	t_token			**token;
	t_command		*cmd;
	int				hd_index;
	int				in_fd;
	int				status;
	int				backup_status;
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

/* <=== ERROR_HANDLER ===> */
void		print_syntax_error(const char *token);
void		print_syscall_error(const char *msg, const int e);
void		print_permission_error(const char *target, t_minishell *mini);
void		print_exec_error(const char *cmd,
				const char *pattern, int code, t_minishell *mini);
void		print_heredoc_error(const char *delimiter);
int			handle_file_not_found(
				const char *cmd, const char *path, t_minishell *mini);
int			handle_file_type_error(const char *cmd, const char *path,
				struct stat sb, t_minishell *mini);

void		status_manager(int *status, int *backup);

/*  <=== SIGNALHANDLER ===>  */
void		handle_signal(int sig);
void		quit_message(void);
void		setup_signals(void);
int			observe_sigint(char *line, int bit);
int			handle_heredoc_signal(void);
int			handle_mainprompt_signal(void);

/* <=== ENVIROMENT ===> */
char		*get_bin_path(t_envlist *list, char *cmd);

/*  <=== TOKENIZER ===>  */
t_token		**ft_lexer(char *line, t_minishell *mini);

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

/*  <=== COMMAND AND HEREDOCUMENTS ===>  */
t_command	*build_commands(t_token **tokens, int count);
t_heredoc	*create_hd_node(char *filename, int fd);
char		**rebuild_args(t_command *cmd);
void		*heredoc_loop(int fd, char *delimiter, int s, t_envlist *e);
void		append_hd_node(t_heredoc **head, t_heredoc *new_node);
void		handle_heredoc(t_command *cmd,
	int *index, int status, t_envlist *env);
	
	/*  <=== REDIRECTION ===>  */
t_rdir		*init_redirect(void);
int			parse_redirects(t_command *cmd, t_rdir *info);
int			valid_redirect_sequence(char **av);
int			apply_redirects(t_rdir *info);
char		**prepare_exec_argv(char **argv, int *argc, int i, int j);
void		set_backup_fd(t_rdir *info);
void		restore_backup_io(t_rdir *info);
int			get_redirect_mode(char *arg);

/*  <=== EXPASION ===>  */
void		init_expand_state(t_state *state);
char		*expand_variables(const char *input, int status, t_envlist *e);
char		*expand_special_variable(const char *str, int status);
char		*remove_quotes(const char *input);
void		state_toggle(t_state *state, int flag);

/*  <=== EXECUTION ===>  */
int			parse_exit_status(int status);
void		exec_bin(t_rdir *i,	t_command *cmd, int *p, t_minishell *mini);
void		expand_and_clean_args(t_command *cmd, t_minishell *mini);
void		exec_pattern(t_command *c, int *p, t_minishell *m, t_rdir *i);
int			process_heredoc(t_command *cmd, int *pipe, t_minishell *mini);
int			parse_exit_status(int status);
void		free_info(t_rdir *info);
int			get_exit_status(t_minishell *mini);
void		ft_exec_v7(t_minishell *mini);

/*  <=== CLEANUP ===>  */
void		ft_clean(t_minishell *mini, int flag);
void		ft_clean_child(t_minishell *mini);
void		ft_clean_exit(t_minishell *mini);

#endif
