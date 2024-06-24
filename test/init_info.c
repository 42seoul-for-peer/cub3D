/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_info.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeunkim <hyeunkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 16:22:39 by hyeunkim          #+#    #+#             */
/*   Updated: 2024/06/24 19:02:38 by hyeunkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	*init_texture(t_info *info, char *path)
{
	t_img	*texture;

	texture = ft_calloc(1, sizeof(t_img));
	if (!texture)
		print_error(sys_call, __func__, __LINE__);
	texture->ptr = mlx_xpm_file_to_image(info->mlx, path, \
											&texture->w, &texture->h);
	if (!texture->ptr)
		print_error(lib_mlx, __func__, __LINE__);
	texture->addr = (int *)mlx_get_data_addr(texture->ptr, &texture->bpp, \
												&texture->line, &texture->endian);
	if (!texture->addr)
		print_error(lib_mlx, __func__, __LINE__);
	return (texture);
}

t_map	*init_map(int fd)
{
	t_map	*map;

	map = ft_calloc(1, sizeof(t_map));
	if (!map)
		print_error(sys_call, __func__, __LINE__);
	set_map_data(map, fd);
	if (check_map_format(map) == false)
		print_error(map_data, __func__, __LINE__);
	return (map);
}

void	init_mlx_info(t_info *info)
{
	info->mlx = mlx_init();
	if (!info->mlx)
		print_error(lib_mlx, __func__, __LINE__);
	info->scr = ft_calloc(1, sizeof(t_img));
	if (!info->scr)
		print_error(sys_call, __func__, __LINE__);
	info->win = mlx_new_window(info->mlx, WIN_W, WIN_H, "cub3D");
	info->scr->ptr = mlx_new_image(info->mlx, WIN_W, WIN_H);
	if (!info->win || !info->scr->ptr)
		print_error(lib_mlx, __func__, __LINE__);
	info->scr->addr = (int *) mlx_get_data_addr(info->scr->ptr, &(info->scr->bpp), \
									&(info->scr->line), &(info->scr->endian));
	if (!info->scr->ptr)
		print_error(lib_mlx, __func__, __LINE__);
	info->texture = ft_calloc(1, sizeof(t_tex));
	if (!info->texture)
		print_error(sys_call, __func__, __LINE__);
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
		print_error(sys_call, __func__, __LINE__);
	info->map = init_map(fd);
	init_mlx_info(info);
	return (info);
}
