/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeunkim <hyeunkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 13:08:37 by hyeunkim          #+#    #+#             */
/*   Updated: 2024/06/17 15:37:21 by hyeunkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_color(char *line)
{
	int	comma_cnt;
	int	num_cnt;

	comma_cnt = 0;
	num_cnt = 0;
	while (*line)
	{
		if (ft_isdigit(*line))
		{
			num_cnt++;
			if (ft_atoi(line) < 0 || ft_atoi(line) > 255)
				print_error(map_data, __func__);
			while (ft_isdigit(*line))
				line++;
		}
		if (*line == ',')
			comma_cnt++;
		line++;
	}
	if (comma_cnt > 2 || num_cnt > 3)
		print_error(map_data, __func__);
}

void	check_elem(char *line, int *elem_arr)
{
	static int	idx;
	int			fd;
	char		*path;

	if (idx > 5)
		print_error(map_data, __func__);
		elem_arr[idx] += 1;
	if (idx < 4)
	{
		line += 2;
		while (ft_isspace(*line))
			line++;
		path = ft_strtrim(line, "\n");
		if (!path)
			print_error(sys_call, __func__);
		fd = open(path, O_RDONLY);
		free(path);
		if (fd < 0)
			print_error(tex, __func__);
		close(fd);
	}
	else
		check_color(line);
	idx++;
}

void	check_scene(char *line, int *scene_arr)
{
	int	len;
	int	idx;

	len = ft_strlen(line);
	if (scene_arr[1] < len)
		scene_arr[1] = len;
	scene_arr[2] += 1;
	idx = 0;
	while (idx < len - 1)
	{
		if (line[idx] == 'N' || line[idx] == 'S' || line[idx] == 'W' || line[idx] == 'E')
			scene_arr[0] += 1;
		else if (line[idx] != '0' && line[idx] != '1')
			print_error(map_data, __func__);
		idx++;
	}
	if (scene_arr[0] > 1)
		print_error(map_data, __func__);
}

void	check_map_data(int fd, int *map_size)
{
	char	*line;
	int		elem[6];
	int		scene[3];

	ft_memset(elem, 0, sizeof(int) * 6);
	ft_memset(scene, 0, sizeof(int) * 3);
	line = get_next_line(fd);
	while (line)
	{
		if (*line != '\n')
		{
			if (ft_isalpha(*line))
				check_elem(line, elem);
			else
				check_scene(line, scene);
		}
		free(line);
		line = get_next_line(fd);
	}
	if (elem[0] & elem[1] & elem[2] & elem[3] & elem[4] & elem[5] != 1)
		print_error(map_data, __func__);
	if (scene[0] != 1 || scene[1] < 3 || scene[2] < 3)
		print_error(map_data, __func__);
	map_size[0] = scene[1];
	map_size[1] = scene[2];
}

int	*check_format(char *file)
{
	int		fd;
	int		*map_size;

	map_size = ft_calloc(2, sizeof(int));
	if (!map_size)
		print_error(sys_call, __func__);
	check_file(file, &fd);
	check_map_data(fd, map_size);
	close(fd);
	return (map_size);
}
