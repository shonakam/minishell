NAME		:= minishell
CC			:= cc
CFLAGS		:= -Wall -Wextra -Werror -MMD -MP

# --- Colors ---
RESET   := \033[0m
RED     := \033[31m
GREEN   := \033[32m
YELLOW  := \033[33m
BLUE    := \033[34m
MAGENTA := \033[35m
CYAN    := \033[36m
WHITE   := \033[37m
BOLD    := \033[1m
# --------------

READLINE_DIR	:= $(shell brew --prefix readline 2>/dev/null || echo "/usr/local")
INCLUDES		:= -I./includes -I$(READLINE_DIR)/include
LDFLAGS			:= -L$(READLINE_DIR)/lib -lreadline

LIBFT_DIR		:= libft
LIBFT			:= $(LIBFT_DIR)/libft.a
INCLUDES		+= -I$(LIBFT_DIR)/includes

DEBUG ?= 0
ifeq ($(DEBUG), 1)
	OBJS_DIR	:= .out_debug
	MODE_FLAGS	:= -g3 -O0 -DDEBUG_MODE -fsanitize=address
	MODE_MSG	:= $(YELLOW)$(BOLD)Debug Mode$(RESET) (No Optimization, GDB ready)
else
	OBJS_DIR	:= .out
	MODE_FLAGS	:= -O3
	MODE_MSG	:= $(CYAN)$(BOLD)Release Mode$(RESET) (High Optimization)
endif

SRCS_DIR		:= srcs
MODULES			:= lexer parser expander executor utils builtins session
-include $(foreach mod, $(MODULES), $(SRCS_DIR)/$(mod)/_sources.mk)
SRCS			:= $(SRCS_DIR)/main.c \
				$(addprefix $(SRCS_DIR)/session/, $(SESSION_FILES)) \
				$(addprefix $(SRCS_DIR)/lexer/, $(LEXER_FILES)) \
				$(addprefix $(SRCS_DIR)/parser/, $(PARSER_FILES)) \
				$(addprefix $(SRCS_DIR)/expander/, $(EXPANDER_FILES)) \
				$(addprefix $(SRCS_DIR)/executor/, $(EXECUTOR_FILES)) \
				$(addprefix $(SRCS_DIR)/utils/, $(UTILS_FILES)) \
				$(addprefix $(SRCS_DIR)/builtins/, $(BUILTINS_FILES))
OBJS			:= $(addprefix $(OBJS_DIR)/, $(SRCS:.c=.o))

-include $(OBJS:.o=.d)

all: $(LIBFT) $(NAME)

help:
	@echo "$(BOLD)Minishell Build Commands:$(RESET)"
	@echo "  make         - Build Release mode"
	@echo "  make DEBUG=1 - Build Debug mode (fsanitize, g3)"
	@echo "  make clean   - Remove object files"
	@echo "  make fclean  - Remove objects and binary"
	@echo "  make re      - Full rebuild"

$(LIBFT): $(LIBFT_DIR)/Makefile
	@$(MAKE) -C $(LIBFT_DIR) DEBUG=$(DEBUG)

$(LIBFT_DIR)/Makefile:
	@echo "$(RED)Error: libft submodule is missing!$(RESET)"
	@echo "$(YELLOW)Please run: git submodule update --init --recursive$(RESET)"
	@exit 1

$(NAME): $(OBJS) $(LIBFT)
	@echo "--------------------------------------------------"
	@echo "Building $(NAME): $(MODE_MSG)"
	@echo "--------------------------------------------------"
	@$(CC) $(CFLAGS) $(MODE_FLAGS) $(OBJS) $(LIBFT) $(LDFLAGS) -o $(NAME)
	@echo "$(GREEN)$(BOLD)Done! ✨$(RESET)"

$(OBJS_DIR)/%.o: %.c
	@mkdir -p $(@D)
	@echo "Compiling: $(BLUE)$<$(RESET)"
	@$(CC) $(CFLAGS) $(MODE_FLAGS) $(INCLUDES) -c $< -o $@

clean:
	@rm -rf .out*
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re:
	@$(MAKE) fclean
	@$(MAKE) all DEBUG=$(DEBUG)

.PHONY: all help clean fclean re
