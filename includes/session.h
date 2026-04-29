#ifndef SESSION_H
# define SESSION_H

# include <stdio.h>
# include <signal.h>
# include <termios.h>
# include <stdbool.h>
# include "libft.h"

# ifndef WCOREDUMP
#  define WCOREDUMP(status) ((status) & 0x80)
# endif

# define STATUS_SIGINT 130
# define STATUS_SIGQUIT 131

extern volatile sig_atomic_t	g_signal_flag;

typedef struct s_ast_node t_ast_node;
typedef struct s_builtin t_builtin;
typedef struct s_job t_job;

typedef enum e_sig_mode {
	SIG_MODE_IDLE = 0,    /* Parent: Main prompt (readline) */
	SIG_MODE_HEREDOC,     /* Parent/Child: Heredoc mode */
	SIG_MODE_EXEC,        /* Parent: Waiting for child */
	SIG_MODE_CHILD,       /* Child: Running the command */
	SIG_MODE_BACKGROUND,  /* Child: Running in the background */
}	t_sig_mode;

typedef struct s_env {
	char	*key;
	char	*value;
	bool	has_value;
}	t_env;

typedef struct s_job_controller
{
	t_job		*all;         /* Head of the linked list containing all jobs */
	t_job		*fg;          /* Pointer to the current foreground job (NULL if none) */
	t_job		*current;     /* The "current" job, marked with '+' in bash */
	t_job		*previous;    /* The "previous" job, marked with '-' in bash */
	ssize_t		id_counter;   /* Counter to assign the next unique job ID */
}	t_job_controller;

typedef struct s_scope {
	char		*line;
	t_list		*tokens;
	t_list		*tokens_anchor;
	t_ast_node	*ast;
	t_ast_node	**sub_root;
	t_job		*job;
	int			fd_stdio[3];
}	t_scope;

typedef struct s_context {
	void				*stack_base;
	const t_builtin		*builtins;
	t_list				*env_list;
	t_scope				scope;
	t_job_controller	job;
	bool				exit;
	bool				is_err_detected;
	bool				in_pipeline;
	int					subshell_depth;
	int					last_status;
	int					shlvl;
	int					fd_save[2];
}	t_context;

bool	context_init(t_context *ctx, char **envp);
void	context_destroy(t_context *ctx);
void	scope_init(t_scope *scope);
void	scope_clear(t_scope *scope);
t_list	*env_load(char **envp);
t_env	*env_parse_line(char *line);
t_env	*env_new(char *key, char *value, bool has_value);
bool	env_set(t_list **lst, char *line);
t_env	*env_find(t_list *lst, char *target);
void	env_free(void *content);
char	*env_get_value(t_list *env_list, char *target);
bool	env_set_pair(t_list **lst, char *key, char *value);
void	env_list_remove(t_list **head, char *key);

void	signal_set_mode(t_sig_mode mode);
void	signal_check_child(char *args, int status);

#endif /* SESSION_H */
