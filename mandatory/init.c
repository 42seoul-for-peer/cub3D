/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeunkim <hyeunkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 14:31:45 by hyeunkim          #+#    #+#             */
/*   Updated: 2024/06/24 22:09:47 by hyeunkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_vector(t_info *info, char pl_dir)
{
	t_ray	*tmp;

	tmp = info->ray;
	if (pl_dir == 'N')
	{
		tmp->pl_dir->y = -1;
		tmp->plane->x = 1;
	}
	else if (pl_dir == 'S')
	{
		tmp->pl_dir->y = 1;
		tmp->plane->x = -1;
	}
	else if (pl_dir == 'W')
	{
		tmp->pl_dir->x = -1;
		tmp->plane->y = -1;
	}
	else
	{
		tmp->pl_dir->x = 1;
		tmp->plane->y = 1;
	}
}

static void	init_calc(t_info *info)
{
	t_vec	*vec_arr;
	t_coor	*coor_arr;
	t_ray	*tmp;

	vec_arr = ft_calloc(4, sizeof(t_vec));
	coor_arr = ft_calloc(3, sizeof(t_coor));
	if (!vec_arr || !coor_arr)
		exit_with_error(sys_call);
	tmp = info->ray;
	tmp->pl_pos = vec_arr + 0;
	tmp->pl_dir = vec_arr + 1;
	tmp->plane = vec_arr + 2;
	tmp->ray_dir = vec_arr + 3;
	tmp->pl_pos->x = info->map->pos.x + 0.5;
	tmp->pl_pos->y = info->map->pos.y + 0.5;
	init_vector(info, info->map->player_dir);
	tmp->map = coor_arr + 0;
	tmp->step = coor_arr + 1;
	tmp->tex_pos = coor_arr + 2;
}

static void	init_mlx_data(t_info *info)
{
	t_img	*scr;

	scr = info->scr;
	info->mlx = mlx_init();
	if (!info->mlx)
		exit_with_error(lib_mlx);
	info->win = mlx_new_window(info->mlx, WIN_W, WIN_H, "cub3D");
	scr->ptr = mlx_new_image(info->mlx, WIN_W, WIN_H);
	if (!info->win || !scr->ptr)
		exit_with_error(lib_mlx);
	scr->addr = (int *) mlx_get_data_addr(scr->ptr, &(scr->bpp), \
											&(scr->line), &(scr->endian));
	if (!scr->ptr)
		exit_with_error(lib_mlx);
}

static void	init_map_data(t_info *info, char *file, int *map_size)
{
	char	*line;
	int		fd;
	int		elem_cnt;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		exit_with_error(sys_call);
	info->map->w = map_size[X];
	info->map->h = map_size[Y];
	elem_cnt = 0;
	while (elem_cnt < 6)
	{
		line = get_next_line(fd);
		if (*line == 'N' || *line == 'S' || *line == 'W' || *line == 'E')
			set_map_texture(info, line + 2, *line);
		else if (*line == 'F' || *line == 'C')
			set_map_color(info, line, *line);
		elem_cnt++;
		free(line);
	}
	set_map_scene(info->map, fd);
	if (close(fd))
		exit_with_error(sys_call);
	free(map_size);
}

t_info	*init_info(char *file, int *map_size)
{
	t_info	*info;

	info = ft_calloc(1, sizeof(t_info));
	if (!info)
		exit_with_error(sys_call);
	info->map = ft_calloc(1, sizeof(t_map));
	info->texture = ft_calloc(1, sizeof(t_tex));
	info->scr = ft_calloc(1, sizeof(t_img));
	info->ray = ft_calloc(1, sizeof(t_ray));
	if (!info->map || !info->texture || !info->scr || !info->ray)
		exit_with_error(sys_call);
	init_mlx_data(info);
	init_map_data(info, file, map_size);
	if (is_map_valid(info->map) == false)
		exit_with_error(map_data);
	init_calc(info);
	return (info);
}
