#ifndef EXECUTOR_H
# define EXECUTOR_H

# include <limits.h>
# include "libft.h"
# include "error.h"
# include "builtin.h"
# include "session.h"
# include "parser.h"

#define PATH_DEV_NULL "/dev/null"
#define HEREDOC_TMP_PREFIX "/tmp/.minish_hd_"
#define HEREDOC_TMP_MODE 0600

struct s_context;
typedef struct s_context t_context;

struct s_ast_node;
typedef struct s_ast_node t_ast_node;

typedef struct s_job
{
	ssize_t			job_id;
	char			*cmd_line;
	pid_t			*pids;
	size_t			count;
	size_t			capacity;
	bool			is_background;
	struct s_job	*next;
}	t_job;

int		executor(t_context *ctx, t_ast_node *ast);
void	invoke_execve(t_context *ctx, char **argv);
void    job_observe(t_context *ctx);
void	job_free(t_job *job);

#endif /* EXECUTOR_H */
