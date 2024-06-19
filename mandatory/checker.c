/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeunkim <hyeunkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 13:08:37 by hyeunkim          #+#    #+#             */
/*   Updated: 2024/06/19 14:08:18 by hyeunkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_color(char *line, char type, int *elem_cnt)
{
	static int	color_cnt[2];
	int			comma_cnt;

	if (type == 'F' && color_cnt[0] == 0 && ft_strncmp(line, "F ", 2) == 0)
		color_cnt[0] = 1;
	else if (type == 'C' && color_cnt[1] == 0 && ft_strncmp(line, "C ", 2) == 0)
		color_cnt[1] = 1;
	else
		print_error(map_data, __func__, __LINE__);
	line += 2;
	comma_cnt = 0;
	while (line && *line)
	{
		if (ft_atoi(line) < 0 || ft_atoi(line) > 255)
			print_error(map_data, __func__, __LINE__);
		line = ft_strchr(line, ',');
		if (line)
		{
			comma_cnt++;
			line += 1;
		}
	}
	if (comma_cnt > 2)
		print_error(map_data, __func__, __LINE__);
	*elem_cnt += 1;
}

void	check_texture(char *line, char type, int *elem_cnt)
{
	static int	tex_cnt[4];
	char		*path;
	int			fd;

	if (type == 'N' && tex_cnt[0] == 0 && ft_strncmp(line, "NO ", 3) == 0)
		tex_cnt[0] = 1;
	else if (type == 'S' && tex_cnt[1] == 0 && ft_strncmp(line, "SO ", 3) == 0)
		tex_cnt[1] = 1;
	else if (type == 'W' && tex_cnt[2] == 0 && ft_strncmp(line, "WE ", 3) == 0)
		tex_cnt[2] = 1;
	else if (type == 'E' && tex_cnt[3] == 0 && ft_strncmp(line, "EA ", 3) == 0)
		tex_cnt[3] = 1;
	else
		print_error(map_data, __func__, __LINE__);
	path = ft_strtrim(line + 3, " \n");
	if (!path)
		print_error(sys_call, __func__, __LINE__);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		print_error(tex, __func__, __LINE__);
	if (close(fd) < 0)
		print_error(sys_call, __func__, __LINE__);
	*elem_cnt += 1;
}

void	check_scene(char *line, int *scene)
{
	static int	flag;

	if (ft_strchr(line, '1'))
	{
		if (flag == 0)
			flag = 1;
		else if (flag == 2)
			print_error(map_data, __func__, __LINE__);
		scene[2] += 1;
		if (get_rtrim_len(line, " \n") > scene[1])
			scene[1] = get_rtrim_len(line, " \n");
		if (ft_strchr(line, 'N') || ft_strchr(line, 'S') || \
			ft_strchr(line, 'W') || ft_strchr(line, 'E'))
			scene[0] += 1;
	}
	else
		if (flag == 1)
			flag = 2;
	while (*line)
	{
		if (!ft_strchr("NSWE10 \n", *line))
			print_error(map_data, __func__, __LINE__);
		line++;
	}
}

void	check_map_data(int fd, int *map_size)
{
	char	*line;
	int		scene[3];
	int		elem_cnt;

	elem_cnt = 0;
	ft_memset(scene, 0, sizeof(int) * 3);
	line = get_next_line(fd);
	while (line)
	{
		if (elem_cnt < 6)
		{
			if (*line == 'N' || *line == 'S' || *line == 'W' || *line == 'E')
				check_texture(line, *line, &elem_cnt);
			else if (*line == 'F' || *line == 'C')
				check_color(line, *line, &elem_cnt);
		}
		else
			check_scene(line, scene);
		free(line);
		line = get_next_line(fd);
	}
	if (scene[0] != 1 || scene[1] < 3 || scene[2] < 3)
		print_error(map_data, __func__, __LINE__);
	map_size[0] = scene[1];
	map_size[1] = scene[2];
}

void	check_format(char *path, int *map_size)
{
	int		fd;
	char	*name;

	if (ft_strrchr(path, '/'))
		name = ft_strrchr(path, '/') + 1;
	else
		name = path;
	if (ft_strlen(name) < 5)
		print_error(map_file, __func__, __LINE__);
	else if (!ft_strchr(name, '.'))
		print_error(map_file, __func__, __LINE__);
	else if (ft_strncmp(ft_strchr(name, '.'), ".cub", 5))
		print_error(map_file, __func__, __LINE__);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		print_error(sys_call, __func__, __LINE__);
	check_map_data(fd, map_size);
	if (close(fd) < 0)
		print_error(sys_call, __func__, __LINE__);
}
