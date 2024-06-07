#include "cub3d.h"

// 맵 데이터 순서
// NO -> SO -> WE -> EA -> F -> C -> mapdata
// NO~EA : 각 방향의 텍스쳐 경로
// F, C  : 색깔 코드
// ()// NO -> SO -> WE -> EA -> F -> C -> mapdata
// NO~EA : 각 방향의 텍스쳐 경로
// F, C  : 색깔 코드

t_type get_map_line_idx(char *line)
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

void get_map_scene(t_map *map, int fd, char *line)
{
	(void) map;
	(void) fd;
	(void) line;
}


void get_map_texture(t_map *map, t_type line_type, char *line)
{
    int     fd;
    const int   len = ft_strlen(line);
    char    *path;

    path = ft_substr(line, 3, len - 3);
    if (!path)
        error_with_str(ERR_SYSCALL);
    fd = open(path, O_RDONLY);
    if (fd < 0)
        error_with_str(ERR_SYSCALL);
	if (map->north == 0 && line_type == north)
		map->north = fd;
	else if (map->south == 0 && line_type == south)
		map->south = fd;
	else if (map->west == 0 && line_type == west)
		map->west = fd;
	else if (map->east == 0 && line_type == east)
		map->east = fd;
    else
        error_with_str(ERR_MAP);
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
	if (idx != 3) //RGB중에 하나가 빠진 경우
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
	int	checker;

	checker = 0;
	if (line_type == floor)
		checker = get_color(map->floor, line);
	else if (line_type == ceiling)
		checker = get_color(map->ceiling, line);
	if (checker != 0)
		error_with_str(checker);
}

t_map   *get_map_data(t_map *map, int fd)
{
    char	*line;
    t_type  line_type;

    line = get_next_line(fd);
    while (line)
    {
		if (line != 0)
		{
			line_type = get_map_line_idx(line);
			if (0 <= line_type && line_type < 4)
				get_map_texture(map, line_type, line); //get_map_texture
			else if (4 <= line_type && line_type < 6)
				get_map_color(map, line_type, line); // get_color
			else
				get_map_scene(map, fd, line);
			free(line);
		}
        line = get_next_line(fd);
    }
    return (map);
}