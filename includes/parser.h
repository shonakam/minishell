#ifndef PARSER_H
# define PAESER_H

typedef struct	s_command {
	char				**argv;
	int					argc;
	// int					input_fd;
	// int					output_fd;
	// int					append_fd;
	struct s_command	*next;
}				t_command;

t_command	*set_argument(t_command *cmd, char *token);
void		handle_io_redirect(t_command *cmd, t_token **tokens, int *i);
void		handle_append(t_command *cmd, t_token **tokens, int *i);
void		handle_heredoc(t_command *cmd, t_token **tokens, int *i);

#endif