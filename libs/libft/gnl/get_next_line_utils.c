/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeunkim <hyeunkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 21:37:52 by hyeunkim          #+#    #+#             */
/*   Updated: 2023/12/21 15:05:08 by hyeunkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*remove_save(t_save **curr, char **res)
{
	t_save	*tmp;

	if (!(*curr))
		return (NULL);
	tmp = NULL;
	if ((*curr)->prev)
	{
		tmp = (*curr)->prev;
		(*curr)->prev->next = (*curr)->next;
	}
	if ((*curr)->next)
	{
		tmp = (*curr)->next;
		(*curr)->next->prev = (*curr)->prev;
	}
	free((*curr)->save);
	free(*curr);
	*curr = tmp;
	if (res)
		free(*res);
	return (NULL);
}

void	*gnl_memset(void *dst, int val, size_t size)
{
	size_t	idx;
	char	*temp;

	idx = 0;
	temp = (char *)dst;
	while (idx < size)
	{
		temp[idx] = (char)val;
		idx++;
	}
	return (dst);
}

size_t	gnl_strlen(const char *str)
{
	size_t	len;

	len = 0;
	if (str == 0)
		return (len);
	while (str[len])
		len++;
	return (len);
}

ssize_t	gnl_find_nl(const char *str)
{
	size_t	idx;

	idx = 0;
	while (str && *str)
	{
		if (*str == '\n')
			return (idx);
		str++;
		idx++;
	}
	return (GENERAL_ERROR);
}

char	*gnl_strjoin(char *dst, char *src, size_t size)
{
	const size_t	dst_len = gnl_strlen(dst);
	size_t			idx;
	char			*new;

	new = (char *)malloc(sizeof(char) * (dst_len + size + 1));
	if (!new)
	{
		free(dst);
		return (NULL);
	}
	idx = 0;
	while (idx < dst_len && (*dst))
	{
		new[idx] = dst[idx];
		idx++;
	}
	free(dst);
	idx = 0;
	while (idx < size && src[idx])
	{
		new[dst_len + idx] = src[idx];
		idx++;
	}
	new[dst_len + idx] = 0;
	return (new);
}
