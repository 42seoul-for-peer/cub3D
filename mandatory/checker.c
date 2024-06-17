/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeunkim <hyeunkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 13:08:37 by hyeunkim          #+#    #+#             */
/*   Updated: 2024/06/17 19:58:52 by hyeunkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_color(char *line)
{
	int	comma_cnt;
	int	num_cnt;

	comma_cnt = 0;
	num_cnt = 0;
	if (ft_strchr(line, '-'))
		print_error(map_data, __func__, __LINE__);
	while (*line)
	{
		if (*line == '+' || ft_isdigit(*line))
		{
			num_cnt++;
			if (ft_atoi(line) < 0 || ft_atoi(line) > 255)
				print_error(map_data, __func__, __LINE__);
			while (*line == '+' || ft_isdigit(*line))
				line++;
		}
		if (*line == ',')
			comma_cnt++;
		if (*line == 0)
			break ;
		line++;
	}
	if (comma_cnt > 2 || num_cnt > 3)
		print_error(map_data, __func__, __LINE__);
}

void	check_elem(char *line, int *elem)
{
	static int	idx;
	int			fd;
	char		*path;

	if (idx > 5)
		print_error(map_data, __func__, __LINE__);
	elem[idx] += 1;
	if (idx < 4)
	{
		line += 2;
		while (ft_isspace(*line))
			line++;
		path = ft_strtrim(line, "\n");
		if (!path)
			print_error(sys_call, __func__, __LINE__);
		fd = open(path, O_RDONLY);
		free(path);
		if (fd < 0)
			print_error(tex, __func__, __LINE__);
		close(fd);
	}
	else
		check_color(line);
	idx++;
}

bool	check_scene(char *line, int *scene)
{
	int	len;
	int	idx;

	len = ft_strlen(line);
	if (!ft_strchr(line, 'N') && !ft_strchr(line, 'S') && !ft_strchr(line, 'W') \
	&& !ft_strchr(line, 'E') && !ft_strchr(line, '1') && !ft_strchr(line, '0'))
		return (false);
	if (line[len - 1] == '\n')
		len--;
	scene[2] += 1;
	idx = 0;
	while (idx < len - 1)
	{
		if (line[idx] == 'N' || line[idx] == 'S' || \
			line[idx] == 'W' || line[idx] == 'E')
			scene[0] += 1;
		else if (line[idx] != '0' && line[idx] != '1' && line[idx] != ' ')
			print_error(map_data, __func__, __LINE__);
		if (line[idx] == ' ' && !ft_strchr(line + idx, '0') && !ft_strchr(line + idx, '1'))
			len = idx;
		idx++;
	}
	if (scene[1] < len)
		scene[1] = len;
	return (true);
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
		if (*line != '\n' && ft_isalpha(*line))
			check_elem(line, elem);
		else if (*line != '\n' && check_scene(line, scene) == false)
			print_error(map_data, __func__, __LINE__);
		if ((scene[1] || scene[2]) && *line == '\n') // 유효 지도들 사이에 개행만 있는 경우
			print_error(map_data, __func__, __LINE__);
		free(line);
		line = get_next_line(fd);
	}
	if (elem[0] * elem[1] * elem[2] * elem[3] * elem[4] * elem[5] != 1)
		print_error(map_data, __func__, __LINE__);
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
	else if (ft_strchr(name, '.') != ft_strrchr(name, '.'))
		print_error(map_file, __func__, __LINE__);
	else if (ft_strnstr(name, ".cub", ft_strlen(name)) == 0)
		print_error(map_file, __func__, __LINE__);
	else if (ft_strncmp(ft_strnstr(name, ".cub", ft_strlen(name)), ".cub", 5))
		print_error(map_file, __func__, __LINE__);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		print_error(sys_call, __func__, __LINE__);
	check_map_data(fd, map_size);
	close(fd);
}
