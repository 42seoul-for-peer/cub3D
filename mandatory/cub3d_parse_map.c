/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_parse_map.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeunkim <hyeunkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 15:29:22 by hyeunkim          #+#    #+#             */
/*   Updated: 2024/06/12 16:49:50 by hyeunkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_file_len(int fd)
{
	char	*line;
	int		line_cnt;

	line = get_next_line(fd);
	if (!line)
		return (-1);
	line_cnt = 1;
	while (line)
	{
		free(line);
		line_cnt++;
		get_next_line(fd);
	}
	return (line_cnt);
}

t_map	*parse_map(int fd)
{
	t_map	*map;

	map = ft_calloc(1, sizeof(t_map));
	if (!map)
		print_error(sys_call, __func__);
    map = get_map_format(map, fd);
    if (map == NULL)
        print_error(map_data, __func__);
	if (check_map_format(map) == false)
		print_error(map_data, __func__);
    return (map);
}
