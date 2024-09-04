NAME = libftprintf.a
SRCS = ft_printf.c utils.c
OBJS = ${SRCS:.c=.o}
LIBFT_PATH = ./libft
LIBFT = $(LIBFT_PATH)/libft.a
CC = cc
CFLAGS = -Wall -Wextra -Werror
AR = ar rs
RM = rm -f

.c.o:
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

all: ${NAME}

$(NAME): $(LIBFT) ${OBJS}
	cp $(LIBFT) $(NAME)
	${AR} ${NAME} ${OBJS}

# cc ${SRCS}

$(LIBFT):
	make -C $(LIBFT_PATH) all

clean:
	make -C $(LIBFT_PATH) clean
	${RM} ${OBJS} ${B_OBJS}

fclean:	clean
	make -C $(LIBFT_PATH) fclean
	${RM} $(NAME)

re:	fclean all

.PHONY:	all clean fclean re libft
