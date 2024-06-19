/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeunkim <hyeunkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 14:31:45 by hyeunkim          #+#    #+#             */
/*   Updated: 2024/06/19 14:32:14 by hyeunkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	*get_texture_data(t_info *info, char *path)
{
	t_img	*texture;

	texture = ft_calloc(1, sizeof(t_img));
	if (!texture)
		print_error(sys_call, __func__, __LINE__);
	texture->ptr = mlx_xpm_file_to_image(info->mlx, path, \
											&texture->width, &texture->height);
	ft_printf("path: %s\n", path);
	if (!texture->ptr)
		print_error(lib_mlx, __func__, __LINE__);
	texture->addr = (int *)mlx_get_data_addr(texture->ptr, &texture->bpp, \
											&texture->line, &texture->endian);
	if (!texture->addr)
		print_error(lib_mlx, __func__, __LINE__);
	return (texture);
}

void	get_mlx_data(t_info *info)
{
	t_img	*scr;

	scr = info->screen;
	info->mlx = mlx_init();
	if (!info->mlx)
		print_error(lib_mlx, __func__, __LINE__);
	info->win = mlx_new_window(info->mlx, WIN_WIDTH, WIN_HEIGHT, "cub3D");
	scr->ptr = mlx_new_image(info->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!info->win || !scr->ptr)
		print_error(lib_mlx, __func__, __LINE__);
	scr->addr = (int *) mlx_get_data_addr(scr->ptr, &(scr->bpp), \
											&(scr->line), &(scr->endian));
	if (!scr->ptr)
		print_error(lib_mlx, __func__, __LINE__);
	info->texture->north = get_texture_data(info, info->map->north);
	info->texture->south = get_texture_data(info, info->map->south);
	info->texture->west = get_texture_data(info, info->map->west);
	info->texture->east = get_texture_data(info, info->map->east);
}

bool	is_surrounded(t_map *map, int x, int y)
{
	char	elem_up;
	char	elem_down;
	char	elem_left;
	char	elem_right;

	if (y == 0 || y == map->height - 1)
		return (false);
	if (x == 0 || x == map->width - 1)
		return (false);
	elem_up = map->scene[y - 1][x];
	elem_down = map->scene[y + 1][x];
	elem_left = map->scene[y][x + 1];
	elem_right = map->scene[y][x - 1];
	if (elem_up == 0 || elem_down == 0 || elem_right == 0 || elem_left == 0)
		return (false);
	if (elem_up == ' ' || elem_down == ' ' || \
			elem_right == ' ' || elem_left == ' ')
		return (false);
	return (true);
}

bool	is_map_valid(t_map *map)
{
	char	elem;
	int		x;
	int		y;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width && map->scene[y][x])
		{
			elem = map->scene[y][x];
			if (elem == 'N' || elem == 'S' || elem == 'W' || elem == 'E')
			{
				map->pos.x = x;
				map->pos.y = y;
				map->player_dir = elem;
				map->scene[y][x] = 'P';
			}
			else if (elem != ' ' && elem != '1' && !is_surrounded(map, x, y))
				return (false);
			x++;
		}
		y++;
	}
	return (true);
}

t_info	*init_info(char *file, int *map_size)
{
	t_info	*info;
	int		fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		print_error(sys_call, __func__, __LINE__);
	info = ft_calloc(1, sizeof(t_info));
	if (!info)
		print_error(sys_call, __func__, __LINE__);
	info->map = ft_calloc(1, sizeof(t_map));
	info->texture = ft_calloc(1, sizeof(t_tex));
	info->screen = ft_calloc(1, sizeof(t_img));
	if (!info->map || !info->texture || !info->screen)
		print_error(sys_call, __func__, __LINE__);
	get_map(info->map, fd, map_size);
	int idx = 0;
	ft_printf("map size : (%d, %d)\n", info->map->width, info->map->height);
	while (info->map->scene[idx])
		ft_printf("[%s]\n", info->map->scene[idx++]);
	if (is_map_valid(info->map) == false)
		print_error(map_data, __func__, __LINE__);
	get_mlx_data(info);
	return (info);
}
