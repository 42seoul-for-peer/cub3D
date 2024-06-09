/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_get_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeunkim <hyeunkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 16:07:06 by hyeunkim          #+#    #+#             */
/*   Updated: 2024/06/09 17:05:14 by hyeunkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void dev_print_mapFormat2(char **map)
{
	int idx = 0;
	ft_printf("-----------------------------------\n");
	while (map[idx][0] != 0)
	{
		ft_printf("%s\n", map[idx]);
		idx++;
	}
	ft_printf("-----------------------------------\n");
}

t_type get_map_line_type(char *line)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
		return (north);
	else if (ft_strncmp(line, "SO ", 3) == 0)
		return (south);
	else if (ft_strncmp(line, "WE ", 3) == 0)
		return (west);
	else if (ft_strncmp(line, "EA ", 3) == 0)
		return (east);
	else if (ft_strncmp(line, "F ", 2) == 0)
		return (floor);
	else if (ft_strncmp(line, "C ", 2) == 0)
		return (ceiling);
	else
		return (scene);
}

char	**get_map_scene_append(char **prev_scene, char *line)
{
	char		**new_scene;
	static int	max_width;
	static int	height;
	int			idx;

	ft_printf("newline\n");
	ft_printf("%s\n", line);
	new_scene = ft_calloc(++height + 1, sizeof(char *));
	if (!new_scene)
		error_with_str(ERR_SYSCALL);
	if ((int) ft_strlen(line) > max_width)
		max_width = ft_strlen(line);
	idx = 0;
	while (idx <= height)
	{
		new_scene[idx] = ft_calloc(1, max_width - 1);
		if (!new_scene[idx])
			error_with_str(ERR_SYSCALL);
		if (idx == height - 1)
			ft_strlcpy(new_scene[idx], line, ft_strlen(line));
		else if (idx != height)
			ft_strlcpy(new_scene[idx], prev_scene[idx], max_width);
		idx++;
	}
	return (new_scene);
}

void get_map_scene(t_map *map, int fd, char *line)
{
	char	**prev_scene;

	while (line)
	{
		prev_scene = map->scene;
		map->scene = get_map_scene_append(prev_scene, line);
		dev_print_mapFormat2(map->scene);
		free(prev_scene);
		free(line);
		line = get_next_line(fd);
	}
}


void get_map_texture(t_map *map, t_type line_type, char *line)
{
    int     fd;
    const int   len = ft_strlen(line);
    char    *path;

    path = ft_substr(line, 3, len - 4);
    if (!path)
        print_error(ERR_SYSCALL);
    fd = open(path, O_RDONLY);
	free(path);
	free(path);
    if (fd < 0)
        print_error(ERR_SYSCALL);
	if (map->north == 0 && line_type == north)
		map->north = fd;
	else if (map->south == 0 && line_type == south)
		map->south = fd;
	else if (map->west == 0 && line_type == west)
		map->west = fd;
	else if (map->east == 0 && line_type == east)
		map->east = fd;
    else
        print_error(ERR_MAP);
}

int	get_color(int *rgb, char *str)
{
	int		idx;
	char	**str_arr;

	str_arr = ft_split(str, ',');
	if (!str_arr)
		return (ERR_SYSCALL);
	idx = 0;
	while (str_arr[idx])
		idx++;
	if (idx != 3) //RGB중에 하나가 빠진 경우 또는 이미 값이 존재하는 경우
		return (ERR_MAP);
	rgb[0] = ft_atoi(str_arr[0] + 1);
	rgb[1] = ft_atoi(str_arr[1]);
	rgb[2] = ft_atoi(str_arr[2]);
	while (idx < 3)
	{
		free(str_arr[idx]);
		idx++;
	}
	free(str_arr);
	return (0);
}

void get_map_color(t_map *map, t_type line_type, char *line)
{
	int	*color_arr;
	int	checker;

	color_arr = ft_calloc(3, sizeof(int));
	if (!color_arr)
		print_error(ERR_SYSCALL);
	checker = get_color(color_arr, line);
	if (checker)
		print_error(checker);
	if (line_type == floor && map->floor == NULL)
		map->floor = color_arr;
	else if (line_type == ceiling && map->ceiling == NULL)
		map->ceiling = color_arr;
	else
		print_error(ERR_MAP);
}

t_map   *get_map_data(t_map *map, int fd)
{
    char	*line;
    t_type  line_type;

    line = get_next_line(fd);
	if (!line)
		return (NULL);
    while (line)
    {
		if (*line != '\n')
		{
			line_type = get_map_line_type(line);
			if (0 <= line_type && line_type < 4)
				get_map_texture(map, line_type, line); //get_map_texture
			else if (4 <= line_type && line_type < 6)
				get_map_color(map, line_type, line); // get_color
			else
				break ;
			line_type++;
		}
		free(line);
        line = get_next_line(fd);
    }
	get_map_scene(map, fd, line);
    return (map);
}
