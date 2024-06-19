/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_format_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeunkim <hyeunkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 14:38:30 by hyeunkim          #+#    #+#             */
/*   Updated: 2024/06/19 14:48:38 by hyeunkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_map_color(t_map *map, char *line, char type)
{
	int		idx;
	int		*rgb;

	rgb = ft_calloc(3, sizeof(int));
	if (!rgb)
		print_error(sys_call, __func__, __LINE__);
	idx = 0;
	while (*line && idx < 3)
	{
		while (!ft_isdigit(*line))
			line++;
		rgb[idx] = ft_atoi(line);
		while (ft_isdigit(*line))
			line++;
		idx++;
	}
	if (type == 'F')
		map->floor = rgb;
	else if (type == 'C')
		map->ceiling = rgb;
}

void	set_map_texture(t_map *map, char *str, char type)
{
	char	*path;

	while (ft_isspace(*str))
		str++;
	path = ft_strtrim(str, "\n");
	if (!path)
		print_error(sys_call, __func__, __LINE__);
	ft_printf("%c, %s\n", type, path);
	if (type == 'N')
		map->north = path;
	else if (type == 'S')
		map->south = path;
	else if (type == 'W')
		map->west = path;
	else if (type == 'E')
		map->east = path;
}

void	get_map_scene(t_map *map, int fd, int *map_size)
{
	int		idx_y;
	int		len;
	int		len_strlcpy;
	char	*line;
	char	**scene;

	idx_y = 0;
	scene = ft_calloc(map_size[Y] + 1, sizeof(char *));
	if (!scene)
		print_error(sys_call, __func__, __LINE__);
	while (idx_y < map_size[Y])
	{
		line = get_next_line(fd);
		if (line && *line != '\n')
		{
			scene[idx_y] = ft_calloc(map_size[X] + 1, sizeof(char));
			if (!scene[idx_y])
				print_error(sys_call, __func__, __LINE__);
			len = ft_strlen(line);
			if (line[len - 1] == '\n')
				len--;
			len_strlcpy = ft_strlcpy(scene[idx_y], line, len + 1);
			idx_y++;
		}
		free(line);
	}
	map->scene = scene;
}

void	set_map(t_map *map, char *file, int *map_size)
{
	int		idx;
	char	*line;
	int		fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		print_error(sys_call, __func__, __LINE__);
	idx = 0;
	map->width = map_size[X];
	map->height = map_size[Y];
	while (idx < 6)
	{
		line = get_next_line(fd);
		if (line && *line != '\n')
		{
			if (*line == 'N' || *line == 'S' || *line == 'W' || *line == 'E')
				set_map_texture(map, line + 3, *line);
			else if (*line == 'F' || *line == 'C')
				set_map_color(map, line, *line);
			idx++;
		}
		free(line);
	}
	get_map_scene(map, fd, map_size);
	close(file);
}
