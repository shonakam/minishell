/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosh <mosh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 22:30:36 by kmoshker          #+#    #+#             */
/*   Updated: 2024/04/23 23:47:53 by mosh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10000
# endif

# include <unistd.h>
# include <limits.h>
# include <stdlib.h>
# include "ft_printf/ft_printf.h"

typedef struct s_list
{
	int				content;
	int				index;
	struct s_list	*next;
}					t_list;

int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
size_t	ft_strlen(const char *s);
int		ft_istrlen(const char *s);
void	*ft_memset(void *b, int c, size_t len);
void	ft_bzero(void *s, size_t n);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_memmove(void *dst, const void *src, size_t len);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
int		ft_toupper(int c);
int		ft_tolower(int c);
char	*ft_strcat(char *dst, const char *src);
char	*ft_strcpy(char *dst, const char *src);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
long	ft_atoi(const char *str);
void	*ft_calloc(size_t count, size_t size);
char	*ft_strdup(const char *s1);
char	*ft_strnstr(const char *str, const char *to_find, size_t len);
// void	ft_putnbr_fd(int n, int fd);
// void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
// void	ft_putchar_fd(char c, int fd);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(const char *s1, const char *s2);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char	*ft_strtrim(char const *s1, char const *set);
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
char	*ft_itoa(int n);
char	**ft_split(char const *str, char charset);
int		count_words(const char *s, char c);
void	ft_lstadd_back(t_list **lst, t_list *new);
t_list	*ft_lstlast(t_list *lst);
int		ft_lstsize(t_list *lst);
void	ft_lstadd_front(t_list **lst, t_list *new);
t_list	*ft_lstnew(int content);
void	ft_lstclear(t_list **lst, void (*del)(int));
void	ft_lstdelone(t_list *lst, void (*del)(int));
void	ft_lstiter(t_list *lst, void (*f)(int));
// t_list	*ft_lstmap(t_list *lst, void *(*f)(int), void (*del)(int));
int		ft_abs(int num);
char	*get_next_line(int fd);
#endif