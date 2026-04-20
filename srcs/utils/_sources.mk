UTILS_FILES := \
core/fd_utils.c \
core/process_utils.c \
core/stack_utils.c \
free_matrix.c \
is_operator.c \
is_redirect.c \
join_three.c \
safe_exit.c \
x_calloc.c \
x_dup.c \
x_dup2.c \
x_fork.c \
x_lstnew.c \
x_open.c \
x_pipe.c \
x_realloc.c \
x_strdup.c \
x_strndup.c \
x_substr.c \

ifeq ($(DEBUG), 1)
	UTILS_FILES += debug/d.c
	UTILS_FILES += debug/debug_print_ast.c
	UTILS_FILES += debug/debug_print_env.c
	UTILS_FILES += debug/debug_print_job.c
	UTILS_FILES += debug/debug_print_list.c
	UTILS_FILES += debug/debug_print_token.c
endif
