/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeunkim <hyeunkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 13:08:37 by hyeunkim          #+#    #+#             */
/*   Updated: 2024/06/25 13:28:54 by hyeunkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	check_color(char *line, int *elem_cnt)
{
	static int	color[2];

	if (color[0] == 0 && ft_strncmp(line, "F ", 2) == 0)
		color[0] = 1;
	else if (color[1] == 0 && ft_strncmp(line, "C ", 2) == 0)
		color[1] = 1;
	else
		exit_with_error(map_data);
	check_color_value(line);
	*elem_cnt += 1;
}

static void	check_texture(char *line, int *elem_cnt)
{
	static int	tex_cnt[4];
	char		*path;
	int			fd;

	if (tex_cnt[0] == 0 && ft_strncmp(line, "NO ", 3) == 0)
		tex_cnt[0] = 1;
	else if (tex_cnt[1] == 0 && ft_strncmp(line, "SO ", 3) == 0)
		tex_cnt[1] = 1;
	else if (tex_cnt[2] == 0 && ft_strncmp(line, "WE ", 3) == 0)
		tex_cnt[2] = 1;
	else if (tex_cnt[3] == 0 && ft_strncmp(line, "EA ", 3) == 0)
		tex_cnt[3] = 1;
	else
		exit_with_error(map_data);
	path = ft_strtrim(line + 3, " \n");
	if (!path)
		exit_with_error(sys_call);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		exit_with_error(tex);
	if (close(fd) < 0)
		exit_with_error(sys_call);
	free(path);
	*elem_cnt += 1;
}

static int	*check_scene(int fd)
{
	int		player;
	int		*map_size;
	char	*line;

	map_size = ft_calloc(2, sizeof(int));
	if (!map_size)
		exit_with_error(sys_call);
	line = get_next_line(fd);
	player = 0;
	while (line)
	{
		check_scene_line(line, &player, map_size);
		free(line);
		line = get_next_line(fd);
	}
	if (player != 1 || map_size[0] < 3 || map_size[1] < 3)
		exit_with_error(map_data);
	return (map_size);
}

static int	check_file_name(char *path)
{
	int		fd;
	char	*name;

	if (ft_strrchr(path, '/'))
		name = ft_strrchr(path, '/') + 1;
	else
		name = path;
	if (ft_strlen(name) < 5)
		exit_with_error(map_file);
	else if (!ft_strchr(name, '.'))
		exit_with_error(map_file);
	else if (ft_strncmp(ft_strchr(name, '.'), ".cub", 5))
		exit_with_error(map_file);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		exit_with_error(sys_call);
	return (fd);
}

int	*check_format(char *path)
{
	int		fd;
	int		elem_cnt;
	int		*map_size;
	char	*line;

	fd = check_file_name(path);
	elem_cnt = 0;
	while (elem_cnt < 6)
	{
		line = get_next_line(fd);
		if (!line)
			exit_with_error(map_data);
		if (*line == 'N' || *line == 'S' || *line == 'W' || *line == 'E')
			check_texture(line, &elem_cnt);
		else if (*line == 'F' || *line == 'C')
			check_color(line, &elem_cnt);
		free(line);
	}
	map_size = check_scene(fd);
	if (close(fd) < 0)
		exit_with_error(sys_call);
	return (map_size);
}
