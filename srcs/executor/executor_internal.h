#ifndef EXECUTOR_INTERNAL_H
# define EXECUTOR_INTERNAL_H

# include "executor.h"
# include <sys/wait.h>
# include <dirent.h>
# include <fcntl.h>
# include <sys/stat.h>

# include "lexer.h"
# include "parser.h"
# include "executor.h"
# include "builtin.h"
# include "utils.h"

typedef enum e_job_state
{
	STATE_RUNNING,
	STATE_DONE,
	STATE_TERMINATED
}	t_job_state;

typedef struct s_pipeline_state
{
	int		p_fd[2];
	int		prev_read_end;
	pid_t	last_pid;
	bool	old_in_pipeline;
}	t_pipeline_state;

typedef struct s_pipeline_manager
{
	int		p[2];
	int		pr_fd;
	int		i;
	pid_t	pid;
}	t_pipeline_manager;

typedef void (*t_engine_func)(t_context *ctx, t_ast_node *node);

void	traverse_ast(t_context *ctx, t_ast_node *node);
void	exec_engine(t_context *ctx, t_ast_node *node);

void	oneshot(t_context *ctx, t_ast_node *node);
void	exec_command(t_context *ctx, t_ast_node *cmd);
void    exec_pipeline(t_context *ctx, t_ast_node *cmd);
void    exec_subshell(t_context *ctx, t_ast_node *cmd);
void	exec_background(t_context *ctx, t_ast_node *node);

t_job	*job_create(t_context *ctx, char *cmd_line, bool is_background);
char	*ast_to_str(t_ast_node *node);
char	*get_redir_symbol(t_redir_type type);
size_t	get_total_len(t_list *args);
void	job_list_append(t_context *ctx, t_job *new_job);
bool	job_add_pid(t_job *job, pid_t pid);
void	job_free(t_job *job);
void	job_clear(t_context *ctx);
void	job_wait(t_context *ctx, t_job *job);

bool	redirect_apply(t_list *redirects);
bool	heredoc_prepare_all(t_context *ctx, t_ast_node *node, int *hd_index);
char	*generate_hd_filename(int *hd_index);
bool	save_stdio(t_context *ctx);
void	restore_stdio(t_context *ctx);

char	**env_serialize(t_list *env);
char	*find_path(char *cmd, t_context *ctx);
char	**convert_args_to_argv(t_list *args);

bool	expand_command(t_context *ctx, t_simple_command *cmd);
bool	expand_variable(t_context *ctx, t_simple_command *cmd);
char	*substitute_variables(t_context *ctx, char *str);
bool	handle_node_expansion(t_context *ctx, t_simple_command *cmd,
	t_list **curr, t_list **prev);
char	*append_char(char *s, char c);
bool	handle_word_splitting(t_list **curr, t_list *prev,
	t_simple_command *cmd, char *expanded);
t_list	*arg_node_new(char *content);

bool	expand_wildcard(t_simple_command *cmd);
t_list	*scan_files(char *pattern);

bool	remove_quotes(t_simple_command *cmd);

#endif /* EXECUTOR_INTERNAL_H */
