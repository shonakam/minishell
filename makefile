MINISHELL = minishell
# readlineのpathを指定してね
RPATH :=  -L/opt/homebrew/opt/readline/lib -lreadline

SRC_PATH := ./srcs/
FLAGS := -Wall -Werror -Wextra
HEADERS := -I./includes
LIBS := $(RPATH) -L$(PWD)/libft
CFLAGS := $(FLAGS) $(HEADERS)
# get argument list max size
ARGUMENT_SIZE := $(shell expr $(shell getconf ARG_MAX) / 8)
CFLAGS += -DARGUMENT_SIZE=$(ARGUMENT_SIZE)

# debug
CFLAGS += -fsanitize=address

SRC_LIST := main/minishell.c \
			main/clean.c \
			test/test.c \
			test/print.c \
			lexer/ft_lexer.c \
			lexer/support.c \
			lexer/error.c \
			parser/ft_parser.c \
			parser/build_cmd_utils.c \
			parser/heredoc.c \
			parser/support.c \
			cmd/ft_exec.c \
			cmd/support.c \
			cmd/error.c \
			main/env/env_manager.c \
			main/env/env_convert.c \
			main/env/support.c \

# SRC_DIRS := main test lexer parser cmd main/env
# SRC_LIST := $(shell find $(SRC_DIRS) -name '*.c')
FILES := $(addprefix $(SRC_PATH), $(SRC_LIST))

all: $(MINISHELL)

$(MINISHELL):
	@make -C $(SRC_PATH)libft
	@gcc $(CFLAGS) $(FILES) $(LIBS) $(SRC_PATH)libft/libft.a -o $(MINISHELL)
	@printf "\033[31mS\033[0m"
	@printf "\033[33mU\033[0m"
	@printf "\033[32mC\033[0m"
	@printf "\033[36mC\033[0m"
	@printf "\033[34mE\033[0m"
	@printf "\033[35mS\033[0m"
	@printf "\033[31mS\033[0m"
	@printf "\033[33m!\033[0m"
	@printf "\033[32m!\033[0m\n"

clean:
	make -C $(SRC_PATH)libft clean

fclean: clean
	rm -f $(MINISHELL)
	make -C $(SRC_PATH)libft fclean

re: fclean all

run: re
	@./minishell
