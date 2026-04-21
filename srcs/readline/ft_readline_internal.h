#ifndef FT_READLINE_INTERNL_H
# define FT_READLINE_INTERNL_H

# include <curses.h>
# include <term.h>
# include <stdlib.h>

# include "../libft/libft.h"
# include "ft_readline.h"
# include "minishell.h"
# include "error.h"
# include "session.h"
# include "utils.h"

#define HIST_FILE_NAME	".minishell_history"

#ifndef HISTSIZE
# define HISTSIZE		500   /* Maximum number of lines in memory */
#endif

#ifndef HISTFILESIZE
# define HISTFILESIZE	2000  /* Maximum number of lines in the history file */
#endif

#ifndef RL_BUFF_SIZE
# define RL_BUFF_SIZE	16
#endif

/* ANSI Escape Sequence codes */
#define ESC_SEQ_START  "\033["
#define ESC_CHAR       '\033'

/* Virtual Key Codes based on ANSI standard */
#define KC_UP    'A'
#define KC_DOWN  'B'
#define KC_RIGHT 'C'
#define KC_LEFT  'D'
#define KC_HOME  'H'
#define KC_END   'F'

/* Meta / Control Sequences */
#define SEQ_CTRL_LEFT  "[1;5D"
#define SEQ_CTRL_RIGHT "[1;5C"

# define CRLF				"\r\n"

typedef enum e_key
{
	K_NONE      = 0,
	K_CTRL_D    = 4,
	K_BS		= 8,
	K_TAB       = 9,
	K_LF        = 10,
	K_CR        = 13,
	K_ESC       = 27,
	K_BACKSPACE = 127,
	K_UP        = 1001,
	K_DOWN      = 1002,
	K_LEFT      = 1003,
	K_RIGHT     = 1004,
	K_HOME      = 1005,
	K_END       = 1006,
	K_DELETE    = 1007
}	t_key;

typedef struct s_caps
{
	char	*le; // Cursor Left
	char	*nd; // Cursor Right (Non-destructive space)
	char	*up; // Cursor Up
	char	*dw; // Cursor Down
	char	*cl; // Clear Screen
	char	*cr; // Carriage Return
	char	*ce; // Clear to End of line
	char	*ks; // Keypad Transmit Mode
	char	*ke; // Keypad Local Mode
}   t_caps;

typedef struct s_readline_state {
	char			*prompt;          /* Pointer to the prompt string for redrawing */
	char			*buf;             /* Dynamic buffer to store the entire input line */
	char			*save_buf;        /* Temporary storage for the "current" line when browsing history */
	char			in[RL_BUFF_SIZE]; /* Temporary buffer for the current read operation */
	unsigned char	current_c;        /* The byte currently being processed */
	t_list			*hist_ptr;        /* Pointer to the current history node (NULL if on the new line) */
	size_t			index;            /* Current insertion position (cursor index) in buf */
	size_t			size;             /* Current capacity (allocated size) of buf */
	ssize_t			read;             /* Number of bytes read in the last operation */
	t_caps			*caps;            /* Terminal capability strings for cursor/screen control */
}	t_readline_state;

int		putchar_int(int c);

t_caps	*get_caps(void);
void	init_readline_state(t_readline_state *s, const char *prompt);
void	destroy_readline_state(t_readline_state *s);
bool	termios_change_to_raw();
bool	termios_change_to_shell_default();

bool	controller(t_readline_state *s);
bool	handle_eot(t_readline_state *s);
bool	handle_newline(t_readline_state *s);
void	handle_backspace(t_readline_state *s);
int		handle_cursor(t_readline_state *s, int index);
void	ft_history_move(t_readline_state *s, int direction);

char	*get_history_path(void);
t_list	**ft_get_history(void);

#endif /* FT_READLINE_INTERNL_H */
