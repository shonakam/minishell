NAME = minishell

# readlineのpathを指定してね
# readlineのpathを指定
RPATH := -L/opt/homebrew/Cellar/readline/8.2.13/lib -lreadline
CFLAGS := -Wall -Werror -Wextra
HEADERS := -I./ -I/opt/homebrew/Cellar/readline/8.2.13/include
LIBS := $(RPATH) -L$(PWD)/libft
CFLAGS := $(FLAGS) $(HEADERS)

# get argument list max size
ARGUMENT_SIZE := $(shell expr $(shell getconf ARG_MAX) / 8)
CFLAGS += -DARGUMENT_SIZE=$(ARGUMENT_SIZE)

# debug
# CFLAGS += -fsanitize=address -g -fno-omit-frame-pointer
# CFLAGS += -g -fsanitize=address
# CFLAGS += -g -fsanitize=leak

# SRC_DIRS := main test lexer parser cmd main/env
# SRC_LIST := $(shell find $(SRC_DIRS) -name '*.c')
# FILES := $(addprefix $(SRC_PATH), $(SRC_LIST))
SRC_PATH := ./srcs/
SRCS := $(shell find $(SRC_PATH) -type f -name '*.c')
OBJS := $(patsubst $(SRC_PATH)%.c, objs/%.o, $(SRCS))

all: $(NAME)

$(NAME): $(OBJS)
	@make -C libft
	@gcc $(CFLAGS) $(OBJS) $(LIBS) libft/libft.a -o $(NAME)
	@printf "\033[31mS\033[0m"
	@printf "\033[33mU\033[0m"
	@printf "\033[32mC\033[0m"
	@printf "\033[36mC\033[0m"
	@printf "\033[34mE\033[0m"
	@printf "\033[35mS\033[0m"
	@printf "\033[31mS\033[0m"
	@printf "\033[33m!\033[0m"
	@printf "\033[32m!\033[0m\n"

objs/%.o: $(SRC_PATH)%.c
	@mkdir -p $(dir $@)
	@gcc $(CFLAGS) -c $< -o $@

clean:
	@make -C libft clean
	@rm -rf objs/

fclean: clean
	@rm -f $(NAME)
	@make -C libft fclean

re: fclean all

leak: re
	@valgrind --leak-check=full --show-leak-kinds=all ./minishell

run: re
	@./minishell || { echo "Build or execution failed"; exit 1; }
