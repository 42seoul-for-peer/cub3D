/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_format_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeunkim <hyeunkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 14:38:30 by hyeunkim          #+#    #+#             */
/*   Updated: 2024/06/17 15:59:09 by hyeunkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_type get_line_type(char *line)
{
	if (!line || *line == '\n')
		return (error);
	if (ft_strncmp(line, "NO ", 3) == 0)
		return (north);
	else if (ft_strncmp(line, "SO ", 3) == 0)
		return (south);
	else if (ft_strncmp(line, "WE ", 3) == 0)
		return (west);
	else if (ft_strncmp(line, "EA ", 3) == 0)
		return (east);
	else if (ft_strncmp(line, "F ", 2) == 0)
		return (floor_color);
	else if (ft_strncmp(line, "C ", 2) == 0)
		return (ceiling_color);
	else
		return (scene);
}

void	get_map_color(t_map *map, char *line, t_type line_type)
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
	if (line_type == floor_color)
		map->floor = rgb;
	else if (line_type == ceiling_color)
		map->ceiling = rgb;
}

void get_map_texture(t_map *map, char *line)
{
    const int   len = ft_strlen(line);
    char    *path;
	char	*path_trim;
	int		idx;

    path = ft_substr(line, 3, len - 4);
    if (!path)
        print_error(sys_call, __func__, __LINE__);
	idx = 0;
	while (path[idx] == ' ')
		idx++;
	path_trim = ft_strdup(path + idx);
	if (!path_trim)
		print_error(sys_call, __func__, __LINE__);
	free(path);
	if (map->north == 0)
		map->north = path_trim;
	else if (map->south == 0)
		map->south = path_trim;
	else if (map->west == 0)
		map->west = path_trim;
	else if (map->east == 0)
		map->east = path_trim;
}

void    get_map_scene(t_map *map, char *line, int fd, int *map_size)
{
    char    **scene;
    int     idx_y;

    idx_y = 0;
	map->height = map_size[X];
	map->width = map_size[Y];
    scene = ft_calloc(map_size[Y] + 1, sizeof(char *));
    if (!scene)
        print_error(sys_call, __func__, __LINE__);
    while (idx_y < map_size[Y])
    {
        scene[idx_y] = ft_calloc(map_size[X] + 1, sizeof(char));
        if (!scene[idx_y])
            print_error(sys_call, __func__, __LINE__);
        ft_strlcpy(scene[idx_y], line, ft_strlen(line));
        idx_y++;
        free(line);
        line = get_next_line(fd);
	}
	scene[map_size[Y]] = 0;
	map->scene = scene;
}

void    get_map(t_map *map, int fd, int *map_size)
{
    char    *line;
    t_type  line_type;

    line = get_next_line(fd);
    while (line)
    {
        if (*line != '\n')
        {
            line_type = get_line_type(line);
			if (line_type == north || line_type == south || \
				line_type == west || line_type == east)
				get_map_texture(map, line);
			else if (line_type == floor_color || line_type == ceiling_color)
				get_map_color(map, line, line_type);
			else
				break ;
        }
        free(line);
		line = get_next_line(fd);
    }
    get_map_scene(map, line, fd, map_size);
}
