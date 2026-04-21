# ==============================================================================
#                               PROJECT SETTINGS
# ==============================================================================
NAME		:= minishell
CC			:= cc
CFLAGS		:= -Wall -Wextra -Werror -MMD -MP

# --- Build Modes ---
DEBUG ?= 0
ifeq ($(DEBUG), 1)
	OBJS_DIR	:= .out_debug
	CFLAGS      := $(filter-out -Werror, $(CFLAGS))
	CFLAGS      += -Wno-unused-variable -Wno-unused-parameter
	MODE_FLAGS	:= -g3 -O0 -DDEBUG_MODE -fsanitize=address
	MODE_MSG	:= $(YELLOW)$(BOLD)Debug Mode$(RESET) (No Optimization, GDB ready)
else
	OBJS_DIR	:= .out
	MODE_FLAGS	:= -O3
	MODE_MSG	:= $(CYAN)$(BOLD)Release Mode$(RESET) (High Optimization)
endif


# ==============================================================================
#                               PATHS & FILES
# ==============================================================================
SRCS_DIR        := srcs
LIBFT_DIR       := libft
LIBFT           := $(LIBFT_DIR)/libft.a
INCLUDES        := -I./includes -I$(LIBFT_DIR)/includes
LDFLAGS			:= -ltermcap
SRCS_DIR		:= srcs
MODULES			:= lexer parser executor utils builtin session readline
-include $(foreach mod, $(MODULES), $(SRCS_DIR)/$(mod)/_sources.mk)
SRCS			:= $(SRCS_DIR)/main.c $(SRCS_DIR)/repl.c\
				$(addprefix $(SRCS_DIR)/session/, $(SESSION_FILES)) \
				$(addprefix $(SRCS_DIR)/lexer/, $(LEXER_FILES)) \
				$(addprefix $(SRCS_DIR)/parser/, $(PARSER_FILES)) \
				$(addprefix $(SRCS_DIR)/executor/, $(EXECUTOR_FILES)) \
				$(addprefix $(SRCS_DIR)/utils/, $(UTILS_FILES)) \
				$(addprefix $(SRCS_DIR)/builtin/, $(BUILTIN_FILES)) \
				$(addprefix $(SRCS_DIR)/readline/, $(READLINE_FILES))
OBJS			:= $(addprefix $(OBJS_DIR)/, $(SRCS:.c=.o))


# ==============================================================================
#                               COLORS & STYLE
# ==============================================================================
RESET   := \033[0m
RED     := \033[31m
GREEN   := \033[32m
YELLOW  := \033[33m
BLUE    := \033[34m
MAGENTA := \033[35m
CYAN    := \033[36m
WHITE   := \033[37m
BOLD    := \033[1m


# ==============================================================================
#                               BUILD RULES
# ==============================================================================
-include $(OBJS:.o=.d)

all: $(LIBFT)
	@$(MAKE) $(NAME) -j $(shell nproc 2>/dev/null || echo 4)

help:
	@echo ""
	@echo "$(BOLD)$(CYAN)--- Minishell Build System ---$(RESET)"
	@echo "$(BOLD)Compilation:$(RESET)"
	@echo "  $(GREEN)make$(RESET)             - Build $(NAME) in $(CYAN)Release mode$(RESET) (optimized)"
	@echo "  $(GREEN)make DEBUG=1$(RESET)     - Build $(NAME) in $(YELLOW)Debug mode$(RESET) (fsanitize, g3)"
	@echo "  $(GREEN)make re$(RESET)          - Full rebuild"
	@echo ""
	@echo "$(BOLD)Testing & Quality:$(RESET)"
	@echo "  $(BLUE)make norm$(RESET)        - Run Norminette (filtered) via Docker"
	@echo "  $(BLUE)make valgrind$(RESET)    - Run Valgrind memory check"
	@echo ""
	@echo "$(BOLD)Cleanup:$(RESET)"
	@echo "  $(MAGENTA)make clean$(RESET)       - Remove object files"
	@echo "  $(MAGENTA)make fclean$(RESET)      - Remove objects and binary"
	@echo ""
	@echo "$(BOLD)Development:$(RESET)"
	@echo "  $(WHITE)make help$(RESET)        - Show this help message"
	@echo ""
	@echo "$(BOLD)Current Configuration:$(RESET)"
	@echo "  Mode: $(YELLOW)$(MODE_MSG)$(RESET)"
	@echo "  Compiler: $(WHITE)$(CC)$(RESET)"
	@echo "  Source Count: $(WHITE)$(words $(SRCS)) files$(RESET)"
	@echo "$(BOLD)$(CYAN)------------------------------$(RESET)"

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


# ==============================================================================
#                               UTILITIES
# ==============================================================================
norm:
	@docker compose -f ./.docker/compose.yaml exec -T $(NAME) bash \
		-c "norminette srcs/**/*.c | \
		grep -vE 'INVALID_HEADER|GLOBAL_VAR_DETECTED|OK!'" \
		> .report

valgrind: re
	@valgrind --leak-check=full \
			--show-leak-kinds=all \
			--suppressions=.valgrind.supp \
			--track-fds=yes \
			--trace-children=yes \
			./minishell

-include $(OBJS:.o=.d)

.PHONY: all clean fclean re norm valgrind help
