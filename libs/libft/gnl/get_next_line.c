/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeunkim <hyeunkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 21:35:46 by hyeunkim          #+#    #+#             */
/*   Updated: 2023/12/22 16:28:26 by hyeunkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	connect_save(t_save **curr, t_save **new)
{
	if (!(*curr))
		*curr = *new;
	else if ((*curr)->fd > (*new)->fd)
	{
		if ((*curr)->prev)
			(*curr)->prev->next = *new;
		(*new)->prev = (*curr)->prev;
		(*new)->next = *curr;
		(*curr)->prev = *new;
		*curr = (*curr)->prev;
	}
	else if ((*curr)->fd < (*new)->fd)
	{
		if ((*curr)->next)
			(*curr)->next->prev = *new;
		(*new)->next = (*curr)->next;
		(*new)->prev = *curr;
		(*curr)->next = *new;
		*curr = (*curr)->next;
	}
}

int	search_save(t_save **curr, int fd)
{
	t_save	*new;

	while ((*curr) && (*curr)->fd != fd)
	{
		if ((!(*curr)->prev && !(*curr)->next) \
			|| (!(*curr)->next && (*curr)->fd < fd) \
			|| (!(*curr)->prev && (*curr)->fd > fd) \
			|| (fd < (*curr)->fd && (*curr)->prev->fd < fd) \
			|| ((*curr)->fd < fd && fd < (*curr)->next->fd))
			break ;
		else if ((*curr)->fd > fd)
			*curr = (*curr)->prev;
		else if ((*curr)->fd < fd)
			*curr = (*curr)->next;
	}
	if ((*curr) && (*curr)->fd == fd)
		return (SUCCESS);
	new = (t_save *)malloc(sizeof(t_save));
	if (!new)
		return (MALLOC_ERROR);
	gnl_memset(new, 0, sizeof(t_save));
	new->fd = fd;
	connect_save(curr, &new);
	return (SUCCESS);
}

int	check_save(t_save **curr, char **res)
{
	char			*tmp;
	const size_t	save_len = gnl_strlen((*curr)->save);
	const ssize_t	nl_idx = gnl_find_nl((*curr)->save);

	*res = NULL;
	if (nl_idx < 0)
	{
		(*curr)->read_flag = 1;
		*res = (*curr)->save;
		(*curr)->save = NULL;
	}
	else
	{
		(*curr)->read_flag = 0;
		*res = gnl_strjoin(NULL, (*curr)->save, nl_idx + 1);
		if (!*res)
			return (MALLOC_ERROR);
		tmp = gnl_strjoin(NULL, (*curr)->save + nl_idx + 1, save_len - nl_idx);
		if (!tmp)
			return (MALLOC_ERROR);
		free((*curr)->save);
		(*curr)->save = tmp;
	}
	return (SUCCESS);
}

int	check_buffer(t_save **curr, char **res, char *buffer, ssize_t read_size)
{
	const ssize_t	nl_idx = gnl_find_nl(buffer);

	if (nl_idx < 0)
	{
		(*curr)->read_flag = 1;
		*res = gnl_strjoin(*res, buffer, read_size);
		if (!*res)
			return (MALLOC_ERROR);
	}
	else
	{
		(*curr)->read_flag = 0;
		*res = gnl_strjoin(*res, buffer, nl_idx + 1);
		if (!*res)
			return (MALLOC_ERROR);
		(*curr)->save = \
			gnl_strjoin(NULL, buffer + nl_idx + 1, read_size - nl_idx);
		if (!(*curr)->save)
			return (MALLOC_ERROR);
	}
	if (read_size < BUFFER_SIZE)
		(*curr)->read_flag = 0;
	return (SUCCESS);
}

char	*get_next_line(int fd)
{
	static t_save	*curr;
	char			buffer[BUFFER_SIZE + 1];
	char			*res;
	ssize_t			read_size;

	if (fd < 0 || BUFFER_SIZE <= 0 || search_save(&curr, fd) == MALLOC_ERROR)
		return (NULL);
	if (check_save(&curr, &res) == MALLOC_ERROR || read(fd, NULL, 0) < 0)
		return (remove_save(&curr, &res));
	while (curr && curr->read_flag == 1)
	{
		gnl_memset(buffer, 0, BUFFER_SIZE + 1);
		read_size = read(fd, buffer, BUFFER_SIZE);
		if (read_size < 0)
			return (remove_save(&curr, &res));
		if (check_buffer(&curr, &res, buffer, read_size) == MALLOC_ERROR)
			return (remove_save(&curr, &res));
	}
	if (!*res)
		return (remove_save(&curr, &res));
	return (res);
}
