SRCS = $(shell find . -name '*.c')

NAME = libft.a
CC = cc
CFLAGS = -Wall -Wextra -Werror
OBJS = $(patsubst %.c, objs/%.o, $(SRCS))
AR = ar rs
RM = rm -f

all: $(NAME)

$(NAME): $(OBJS)
	$(AR) $@ $(OBJS)

objs/%.o: %.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -I . -c $< -o $@

clean:
	@$(RM) -r objs

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
