/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeunkim <hyeunkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 16:07:06 by hyeunkim          #+#    #+#             */
/*   Updated: 2024/06/16 17:26:13 by hyeunkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_type get_map_line_type(char *line)
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

char	**get_map_scene_append(char **prev_scene, t_map *map, char *line)
{
	char		**new_scene;
	int			idx;

	new_scene = ft_calloc(++map->height + 1, sizeof(char *));
	if (!new_scene)
		print_error(sys_call, __func__);
	if ((int) ft_strlen(line) > map->width)
		map->width = ft_strlen(line);
	idx = 0;
	while (idx < map->height)
	{
		new_scene[idx] = ft_calloc(1, map->width + 1);
		if (!new_scene[idx])
			print_error(sys_call, __func__);
		if (idx == map->height - 1)
			ft_strlcpy(new_scene[idx], line, ft_strlen(line) + 1);
		else if (idx != map->height)
			ft_strlcpy(new_scene[idx], prev_scene[idx], map->width + 1);
		idx++;
	}
	new_scene[map->height] = 0;
	return (new_scene);
}

void get_map_scene(t_map *map, char *line, int fd)
{
	char	**prev_scene;
	char	*trim_line;

	while (line)
	{
		trim_line = ft_strtrim(line, "\n");
		prev_scene = map->scene;
		map->scene = get_map_scene_append(prev_scene, map, trim_line);
		free(prev_scene);
		free(line);
		free(trim_line);
		line = get_next_line(fd);
	}
}

void get_map_texture(t_map *map, char *line, t_type line_type)
{
    const int   len = ft_strlen(line);
    char    *path;
	char	*path_trim;
	int		idx;

    path = ft_substr(line, 3, len - 4);
    if (!path)
        print_error(sys_call, __func__);
	idx = 0;
	while (path[idx] == ' ')
		idx++;
	path_trim = ft_strdup(path + idx);
	if (!path_trim)
		print_error(sys_call, __func__);
	free(path);
	if (map->north == 0 && line_type == north)
		map->north = path_trim;
	else if (map->south == 0 && line_type == south)
		map->south = path_trim;
	else if (map->west == 0 && line_type == west)
		map->west = path_trim;
	else if (map->east == 0 && line_type == east)
		map->east = path_trim;
    else
	{
		// free(path_trim);
        print_error(map_data, __func__);
	}
}

void	set_rgb(int	*rgb, char *line)
{
	int		idx;
	char	*trim_result;
	char	**split_res;

	while ((9 <= *line && *line <= 13) || *line == 32)
		line++;
	if (!ft_isdigit(*line))
		print_error(map_data, __func__);
	split_res = ft_split(line, ',');
	if (!split_res)
		print_error(sys_call, __func__);
	idx = 0;
	while (idx < 3)
	{
		trim_result = ft_strtrim(split_res[idx], " \n");
		if (!trim_result)
			print_error(sys_call, __func__);
		rgb[idx] = ft_atoi(trim_result);
		if (ft_strchr(trim_result, ' ') || rgb[idx] < 0 || rgb[idx] > 255)
			print_error(map_data, __func__);
		free(trim_result);
		free(split_res[idx++]);
	}
	free(split_res);
}

bool	check_color_format(char *str)
{
	int	cnt;
	int	idx;

	if (*str != 'F' && *str != 'C')
		return (false);
	cnt = 0;
	while (ft_strchr(str, ','))
		cnt++;
	ft_printf("cnt: %d\n", cnt);
	if (cnt > 2)
		return (false);
	idx = 0;
	while (idx < 3)
	{
		while (!ft_isdigit(*str))
			str++;
		if (ft_atoi(str) < 0 || ft_atoi(str) > 255)
			return (false);
		while (ft_isdigit(*str))
			str++;
	}
	return (true);
}

void	get_map_color(t_map *map, char *line, t_type line_type)
{
	int		*rgb;

	rgb = ft_calloc(3, sizeof(int));
	if (!rgb)
		print_error(sys_call, __func__);
	set_rgb(rgb, line + 1);
	if (line_type == floor_color && map->floor == NULL)
		map->floor = rgb;
	else if (line_type == ceiling_color && map->ceiling == NULL)
		map->ceiling = rgb;
	else
		print_error(map_data, __func__);
}

void	set_map_data(t_map *map, int fd)
{
	char	*line;
	t_type	line_type;

	line = get_next_line(fd);
	while (line)
	{
		if (*line != '\n')
		{
			line_type = get_map_line_type(line);
			if (line_type == north || line_type == south || \
				line_type == west || line_type == east)
				get_map_texture(map, line, line_type);
			else if (line_type == floor_color || line_type == ceiling_color)
				get_map_color(map, line, line_type);
			else
				break ;
		}
		free(line);
		line = get_next_line(fd);
	}
	get_map_scene(map, line, fd);
}
