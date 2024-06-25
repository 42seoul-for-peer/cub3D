/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_info.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeunkim <hyeunkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 16:22:39 by hyeunkim          #+#    #+#             */
/*   Updated: 2024/06/24 22:10:08 by hyeunkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	*init_texture(t_info *info, char *path)
{
	t_img	*texture;

	texture = ft_calloc(1, sizeof(t_img));
	if (!texture)
		exit_with_error(sys_call);
	texture->ptr = mlx_xpm_file_to_image(info->mlx, path, \
											&texture->w, &texture->h);
	if (!texture->ptr)
		exit_with_error(lib_mlx);
	texture->addr = (int *)mlx_get_data_addr(texture->ptr, &texture->bpp, \
												&texture->line, &texture->endian);
	if (!texture->addr)
		exit_with_error(lib_mlx);
	return (texture);
}

t_map	*init_map(int fd)
{
	t_map	*map;

	map = ft_calloc(1, sizeof(t_map));
	if (!map)
		exit_with_error(sys_call);
	set_map_data(map, fd);
	if (check_map_format(map) == false)
		exit_with_error(map_data);
	return (map);
}

void	init_mlx_info(t_info *info)
{
	info->mlx = mlx_init();
	if (!info->mlx)
		exit_with_error(lib_mlx);
	info->scr = ft_calloc(1, sizeof(t_img));
	if (!info->scr)
		exit_with_error(sys_call);
	info->win = mlx_new_window(info->mlx, WIN_W, WIN_H, "cub3D");
	info->scr->ptr = mlx_new_image(info->mlx, WIN_W, WIN_H);
	if (!info->win || !info->scr->ptr)
		exit_with_error(lib_mlx);
	info->scr->addr = (int *) mlx_get_data_addr(info->scr->ptr, &(info->scr->bpp), \
									&(info->scr->line), &(info->scr->endian));
	if (!info->scr->ptr)
		exit_with_error(lib_mlx);
	info->texture = ft_calloc(1, sizeof(t_tex));
	if (!info->texture)
		exit_with_error(sys_call);
	info->texture->north = init_texture(info, info->map->north);
	info->texture->south = init_texture(info, info->map->south);
	info->texture->west = init_texture(info, info->map->west);
	info->texture->east = init_texture(info, info->map->east);
}

t_info	*init_info(int fd)
{
	t_info	*info;

	info = ft_calloc(1, sizeof(t_info));
	if (!info)
		exit_with_error(sys_call);
	info->map = init_map(fd);
	init_mlx_info(info);
	return (info);
}
