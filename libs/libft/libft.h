/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeunkim <hyeunkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 17:08:12 by hyeunkim          #+#    #+#             */
/*   Updated: 2024/01/08 18:49:55 by hyeunkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

/* ******************************** HEADER ********************************** */
# include <unistd.h>
# include <stdlib.h>

/* ************************* USER DEFINED STRUCTURE ************************* */
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

/* ******************************* FUNCTIONS ******************************** */
/* int and ascii */
int		ft_atoi(const char *str);
char	*ft_itoa(int n);

/* char determine */
int		ft_isalpha(int val);
int		ft_isdigit(int val);
int		ft_isalnum(int val);
int		ft_isascii(int val);
int		ft_isprint(int val);

/* alter char */
int		ft_tolower(int c);
int		ft_toupper(int c);

/* memory related functions */
void	ft_bzero(void *dst, size_t size);
void	*ft_memset(void *dst, int val, size_t size);
int		ft_memcmp(const void *str1, const void *s2, size_t n);
void	*ft_memcpy(void *dst, const void *src, size_t size);
void	*ft_memchr(const void *str, int val, size_t size);
void	*ft_memmove(void *dst, const void *src, size_t size);

/* string related functions */
int		ft_strncmp(const char *str1, const char *str2, size_t size);
char	*ft_strchr(const char *str, int val);
char	*ft_strrchr(const char *str, int val);
char	*ft_strnstr(const char *haystack, const char *needle, size_t size);
char	*ft_strdup(const char *str);
char	*ft_substr(char const *src, unsigned int start, size_t len);
char	*ft_strjoin(char const *str_pre, char const *str_suf);
char	*ft_strtrim(char const *str1, char const *set);
char	*ft_strmapi(char const *str, char (*f)(unsigned int, char));
void	*ft_striteri(char *str, void (*f)(unsigned int, char*));
char	**ft_split(char const *str, char sep);
size_t	ft_strlen(const char *str);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);

/* linked list related functions */
t_list	*ft_lstnew(void *content);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));
void	ft_lstadd_front(t_list **lst, t_list *new);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstclear(t_list **lst, void (*del)(void *));

/* write functions */
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *str, int fd);
void	ft_putendl_fd(char *str, int fd);
void	ft_putnbr_fd(int n, int fd);

/* memory allocation */
void	*ft_calloc(size_t count, size_t size);

/* ft_printf */
int		ft_printf(const char *format, ...);
char	*ft_ltoa_base(size_t num, char base);

/* get_next_line */
char	*get_next_line(int fd);

#endif
