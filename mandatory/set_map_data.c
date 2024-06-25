/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_map_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeunkim <hyeunkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 14:38:30 by hyeunkim          #+#    #+#             */
/*   Updated: 2024/06/24 22:10:08 by hyeunkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_map_color(t_info *info, char *line, char type)
{
	int		idx;
	int		*rgb;

	rgb = ft_calloc(3, sizeof(int));
	if (!rgb)
		exit_with_error(sys_call);
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
		info->texture->floor = rgb;
	else if (type == 'C')
		info->texture->ceiling = rgb;
}

void	set_map_texture(t_info *info, char *str, char type)
{
	t_img	*texture;

	str = ft_strtrim(str, " \n");
	if (!str)
		exit_with_error(sys_call);
	texture = ft_calloc(1, sizeof(t_img));
	if (!texture)
		exit_with_error(sys_call);
	texture->ptr = mlx_xpm_file_to_image(info->mlx, str, \
											&texture->w, &texture->h);
	if (!texture->ptr)
		exit_with_error(lib_mlx);
	texture->addr = (int *)mlx_get_data_addr(texture->ptr, &texture->bpp, \
											&texture->line, &texture->endian);
	if (!texture->addr)
		exit_with_error(lib_mlx);
	if (type == 'N')
		info->texture->north = texture;
	else if (type == 'S')
		info->texture->south = texture;
	else if (type == 'W')
		info->texture->west = texture;
	else if (type == 'E')
		info->texture->east = texture;
	free(str);
}

void	set_map_scene(t_map *map, int fd)
{
	int		idx_h;
	char	*line;
	char	**scene;

	idx_h = 0;
	scene = ft_calloc(map->h + 1, sizeof(char *));
	if (!scene)
		exit_with_error(sys_call);
	while (idx_h < map->h)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (ft_strchr(line, '1'))
		{
			scene[idx_h] = ft_calloc(map->w + 1, sizeof(char));
			if (!scene[idx_h])
				exit_with_error(sys_call);
			ft_strlcpy(scene[idx_h], line, get_rtrim_len(line, " \n") + 1);
			idx_h++;
		}
		free(line);
	}
	map->scene = scene;
}
