SRCS =	ft_strlen.c \
		ft_strlcpy.c \
		ft_strlcat.c \
		ft_strchr.c \
		ft_strrchr.c \
		ft_strnstr.c \
		ft_strncmp.c \
		ft_strnstr.c \
		ft_memset.c \
		ft_bzero.c \
		ft_memcpy.c \
		ft_memchr.c \
		ft_memmove.c \
		ft_memcmp.c \
		ft_atoi.c \
		ft_abs.c \
		ft_isalpha.c \
		ft_isdigit.c \
		ft_isalnum.c \
		ft_isascii.c \
		ft_isprint.c \
		ft_toupper.c \
		ft_tolower.c \
		ft_calloc.c \
		ft_strdup.c \
		ft_substr.c \
		ft_strjoin.c \
		ft_strtrim.c \
		ft_split.c \
		count_words.c \
		ft_int_strlen.c \
		ft_itoa.c \
		ft_strmapi.c \
		ft_striteri.c\
		ft_putchar_fd.c \
		ft_putstr_fd.c \
		ft_putendl_fd.c \
		ft_putnbr_fd.c \
		ft_lstnew.c \
		ft_lstadd_front.c \
		ft_lstsize.c \
		ft_lstlast.c \
		ft_lstadd_back.c \
		ft_lstdelone.c \
		ft_lstclear.c \
		ft_lstiter.c \
		ft_lstmap.c \
		get_next_line/get_next_line.c \
		ft_printf/ft_printf.c \
		ft_printf/utils.c \

NAME = libft.a
CC = cc
CFLAGS = -Wall -Wextra -Werror
OBJS = $(SRCS:.c=.o)
AR = ar rs
RM = rm -f

all: $(NAME)

$(NAME): $(OBJS)
	$(AR) $@ $(OBJS)
%.o: %.c
	$(CC) $(CFLAGS) -I . -c $< -o $@
clean:
	$(RM) $(OBJS)

fclean:clean
	$(RM) $(NAME)

re:fclean all

.PHONY: all clean fclean re
