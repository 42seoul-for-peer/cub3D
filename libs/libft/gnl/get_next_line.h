/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeunkim <hyeunkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 21:36:00 by hyeunkim          #+#    #+#             */
/*   Updated: 2023/12/21 14:18:13 by hyeunkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

/* ******************************* INCLUDE ********************************** */
# include <unistd.h>
# include <stdlib.h>

/* ******************************** MACRO *********************************** */
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE (40)
# endif
# define GENERAL_ERROR (-1)
# define MALLOC_ERROR (-20)
# define SUCCESS (0)

/* ************************ USER DEFINED STRUCTURE ************************** */
typedef struct s_node
{
	int				fd;
	int				read_flag;
	char			*save;
	struct s_node	*prev;
	struct s_node	*next;
}	t_save;

/* ******************************* FUNCTIONS ******************************** */
/*gnl.c*/
char	*get_next_line(int fd);
/*gnl_u.c*/
void	*remove_save(t_save **curr, char **res);
void	*gnl_memset(void *dst, int val, size_t size);
size_t	gnl_strlen(const char *str);
ssize_t	gnl_find_nl(const char *str);
char	*gnl_strjoin(char *dst, char *src, size_t size);

#endif