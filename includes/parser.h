#ifndef PARSER_H
# define PAESER_H

typedef struct	s_command {
	char				**argv;
	int					argc;
	int					input_fd;
	int					output_fd;
	int					append_fd;
	struct s_command	*next;
}				t_command;

t_command	*set_argument(t_command *cmd, char *token);

#endif