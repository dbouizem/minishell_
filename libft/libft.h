/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fadzejli <fadzejli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 00:50:26 by dbouizem          #+#    #+#             */
/*   Updated: 2026/01/03 13:43:42 by fadzejli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <ctype.h>
# include <stdarg.h>
# include <stdio.h>//Test
# include <limits.h>//Test
# include <stdint.h>//pour utiliser uintmax_t/intmax_t/uintptr_t
# include <stddef.h>//ptrdiff_t

// [ft_printf]
# define DIGITS "0123456789"
# define HEXLOW "0123456789abcdef"
# define HEXUPP "0123456789ABCDEF"

typedef struct s_printf
{
	int			total;
	int			error;
	va_list		args;
}		t_printf;

/*Functions*/
int					ft_printf(const char *formant, ...);

void				parse_format(const char **format, t_printf *data);

void				ft_print_char(char c, t_printf *data);
void				ft_print_str(char *s, t_printf *data);
void				ft_print_ptr(void *ptr, t_printf *data);
void				ft_print_int(int n, t_printf *data);
void				ft_print_u_int(unsigned int n, t_printf *data);
void				ft_print_hex(unsigned int n, int uppercase, t_printf *data);

// [GET_NEXT_LINE]
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

typedef struct s_dynbuf
{
	char	*data;
	size_t	len;
	size_t	capacity;
}	t_dynbuf;

typedef struct s_fd_list
{
	int					fd;
	char				*stock;
	struct s_fd_list	*next;
}	t_fd_list;

char				*ft_gnl(int fd);

t_fd_list			*get_fd_node(t_fd_list **list, int fd);
size_t				ft_strlcpy(char *dst, const char *src, size_t size);
void				remove_fd_node(t_fd_list **list, int fd);
void				*ft_memcpy(void *dest, const void *src, size_t n);
char				*ft_strdup(const char *s);

// [LIBFT]
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}			t_list;

/*
** Part 1
*/

int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
int					ft_tolower(int c);
int					ft_toupper(int c);
int					ft_isspace(char c);
int					ft_isnumber(char *str);

size_t				ft_strlen(const char *str);
size_t				ft_strlcpy(char *dest, const char *src, size_t size);
size_t				ft_strlcat(char *dest, const char *src, size_t n);

void				*ft_memset(void *s, int c, size_t n);
void				ft_bzero(void *s, size_t n);
void				*ft_memcpy(void *dest, const void *src, size_t n);
void				*ft_memmove(void *dest, void *src, size_t n);
void				*ft_memchr(const void *s, int c, size_t n);
void				*ft_calloc(size_t num, size_t size);

char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
char				*ft_strnstr(const char *h, const char *n, size_t len);
char				*ft_strdup(const char *src);

int					ft_strcmp(const char *a, const char *b);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
int					ft_atoi(const char *str);

/*
** Part 2
*/

void				ft_striteri(char *s, void (*f)(unsigned int, char*));
void				ft_putstr_fd(char *s, int fd);
void				ft_putchar_fd(char c, int fd);
void				ft_putendl_fd(char *s, int fd);
void				ft_putnbr_fd(int n, int fd);

char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s1, char const *set);
char				*ft_itoa(int n);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));

char				**ft_split(char const *s, char c);
long long			ft_atoll(const char *str, int *overflow);

/*
** Bonus
*/

t_list				*ft_lstnew(void *content);
t_list				*ft_lstlast(t_list *lst);
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
						void (*del)(void *));

void				ft_lstadd_front(t_list **lst, t_list *new);
void				ft_lstadd_back(t_list **lst, t_list *new);
void				ft_lstdelone(t_list *lst, void (*del)(void *));
void				ft_lstclear(t_list **lst, void (*del) (void *));
void				ft_lstiter(t_list *lst, void (*f)(void *));

int					ft_lstsize(t_list *lst);
char				*ft_strncpy(char *dst, const char *src, size_t n);
char				*ft_strjoin3(char const *s1, char const *s2,
						char const *s3);
void				ft_free_tab(char **tab);

#endif
