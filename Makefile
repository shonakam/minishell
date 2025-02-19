
NAME = minishell

# valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes --trace-children=yes ./minishell

HEADERS := -I./ -I/opt/homebrew/Cellar/readline/8.2.13/include
RL := -L/opt/homebrew/Cellar/readline/8.2.13/lib -lreadline
LIBS := $(RL) -L$(PWD)/libft
CFLAGS := -Wall -Werror -Wextra
CFLAGS += $(HEADERS)

# get argument list max size
ARGUMENT_SIZE := $(shell expr $(shell getconf ARG_MAX) / 8)
CFLAGS += -DARGUMENT_SIZE=$(ARGUMENT_SIZE)

SRC_PATH := ./srcs/
SRCS := \
    $(SRC_PATH)cmd/builtins/builtin_handler.c \
    $(SRC_PATH)cmd/builtins/cd.c \
    $(SRC_PATH)cmd/builtins/echo.c \
    $(SRC_PATH)cmd/builtins/env.c \
    $(SRC_PATH)cmd/builtins/exit.c \
    $(SRC_PATH)cmd/builtins/export.c \
    $(SRC_PATH)cmd/builtins/pwd.c \
    $(SRC_PATH)cmd/builtins/unset.c \
\
    $(SRC_PATH)cmd/executor/execute_bin.c \
    $(SRC_PATH)cmd/executor/execute_handler.c \
    $(SRC_PATH)cmd/executor/ft_exec_v7.c \
    $(SRC_PATH)cmd/executor/parse_status.c \
\
    $(SRC_PATH)cmd/expand/expand.c \
    $(SRC_PATH)cmd/expand/rm_quote.c \
\
    $(SRC_PATH)cmd/heredoc/heredoc_loop.c \
    $(SRC_PATH)cmd/heredoc/heredoc_node.c \
    $(SRC_PATH)cmd/heredoc/heredoc_setup.c \
    $(SRC_PATH)cmd/heredoc/rebuild_cmd.c \
\
    $(SRC_PATH)cmd/redirects/fd_navigate.c \
    $(SRC_PATH)cmd/redirects/redirect_apply.c \
    $(SRC_PATH)cmd/redirects/redirect_parse.c \
\
    $(SRC_PATH)cmd/command_builder.c \
\
    $(SRC_PATH)error/handler.c \
    $(SRC_PATH)error/print_errors.c \
\
	$(SRC_PATH)lexer/ft_lexer.c \
    $(SRC_PATH)lexer/support.c \
    $(SRC_PATH)lexer/tokenizer.c \
    $(SRC_PATH)lexer/valid_context.c \
	$(SRC_PATH)lexer/valid_unsupported_syntax.c \
\
    $(SRC_PATH)main/env/env_convert.c \
    $(SRC_PATH)main/env/env_manager.c \
    $(SRC_PATH)main/env/env_split.c \
    $(SRC_PATH)main/env/get_bin_path.c \
    $(SRC_PATH)main/main.c \
	$(SRC_PATH)main/status.c \
    $(SRC_PATH)main/ft_cleanup.c \
    $(SRC_PATH)main/signal/signal_handler.c \
	$(SRC_PATH)main/signal/signal_rl_event.c \
\
    $(SRC_PATH)utils/cmd.c \
    $(SRC_PATH)utils/expand.c \
    $(SRC_PATH)utils/heredoc.c \
    $(SRC_PATH)utils/redirect.c \
    $(SRC_PATH)utils/env.c \
    $(SRC_PATH)utils/exec.c \
    $(SRC_PATH)utils/file_and_dir.c \
    $(SRC_PATH)utils/token.c \
	$(SRC_PATH)utils/print_debug.c \

OBJS := $(SRCS:$(SRC_PATH)%.c=objs/%.o)

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

run: re
	@./minishell || { echo "Build or execution failed"; exit 1; }
