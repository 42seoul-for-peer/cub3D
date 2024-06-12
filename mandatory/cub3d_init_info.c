/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_init_info.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeunkim <hyeunkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 16:22:39 by hyeunkim          #+#    #+#             */
/*   Updated: 2024/06/12 20:49:19 by hyeunkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_img	*get_texture2(t_info *info, char *file)
{
	t_img	*img;

	img = ft_calloc(1, sizeof(t_img));
	if (!img)
		print_error(sys_call, __func__);
	img->img = mlx_xpm_file_to_image(info->mlx, file, &img->width, &img->height);
	if (!img)
		print_error(map_data, __func__); // mlx error로 바꿀것
	img->addr = mlx_get_data_addr(img->img, &img->bpp, &img->line, &img->endian);
	return (img);
}
void	get_texture(t_info *info)
{
	int 	w;
	int 	h;
	// t_img	*img;

	// img = ft_calloc(1, sizeof(t_img));
	// if (!img)
	// 	print_error(sys_call, __func__);
	// img->img = mlx_xpm_file_to_image(info->mlx, file, &w, &h);
	// if (!img)
	// 	print_error(map_data, __func__); // mlx error로 바꿀것
	// img->addr = mlx_get_data_addr(img->img, &img->bpp, &img->line, &img->endian);
    info->texture->north = mlx_xpm_file_to_image(info->mlx, info->map->north, &w, &h);
    info->texture->south = mlx_xpm_file_to_image(info->mlx, info->map->south, &w, &h);
    info->texture->west = mlx_xpm_file_to_image(info->mlx, info->map->west, &w, &h);
    info->texture->east = mlx_xpm_file_to_image(info->mlx, info->map->east, &w, &h);
    if (!info->texture->north || !info->texture->south || !info->texture->west || !info->texture->east)
        print_error(map_data, __func__);
	// return (img);
}

t_info	*init_info(int fd)
{
	t_info	*info;

	info = ft_calloc(1, sizeof(t_info));
	if (!info)
		print_error(sys_call, __func__);
	info->img = ft_calloc(1, sizeof(t_img));
	if (!info)
		print_error(sys_call, __func__);
	info->map = ft_calloc(1, sizeof(t_map));
	info->texture = ft_calloc(1, sizeof(t_texture));
	if (!info->map || !info->texture)
		print_error(sys_call, __func__);
	info->map = get_map_format(info->map, fd);
	if (!info->map)
		print_error(map_data, __func__);
	if (check_map_format(info->map) == false)
		print_error(map_data, __func__);
    info->mlx = mlx_init();
	info->win_size[0] = 1920;
	info->win_size[1] = 1080;
    info->win = mlx_new_window(info->mlx, 1920, 1080, "test");
	// get_texture(info);
	info->texture->north = get_texture2(info, info->map->north);
	info->texture->south = get_texture2(info, info->map->south);
	info->texture->west = get_texture2(info, info->map->west);
	info->texture->east = get_texture2(info, info->map->east);
	return (info);
}