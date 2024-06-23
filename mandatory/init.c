/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeunkim <hyeunkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 14:31:45 by hyeunkim          #+#    #+#             */
/*   Updated: 2024/06/23 18:13:07 by hyeunkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_vector(t_info *info, char p_dir)
{
	t_data	*tmp_data;

	tmp_data = info->calc;
	if (p_dir == 'N')
	{
		tmp_data->dir->y = -1;
		tmp_data->plane->x = 1;
	}
	else if (p_dir == 'S')
	{
		tmp_data->dir->y = 1;
		tmp_data->plane->x = -1;
	}
	else if (p_dir == 'W')
	{
		tmp_data->dir->x = -1;
		tmp_data->plane->y = -1;
	}
	else
	{
		tmp_data->dir->x = 1;
		tmp_data->plane->y = 1;
	}
}

static void	init_calc(t_info *info)
{
	t_vec	*vec_arr;
	t_coor	*coor_arr;
	t_data	*tmp;

	vec_arr = ft_calloc(4, sizeof(t_vec));
	coor_arr = ft_calloc(2, sizeof(t_coor));
	if (!vec_arr || !coor_arr)
		print_error(sys_call, __func__, __LINE__);
	tmp = info->calc;
	tmp->pos = vec_arr + 0;
	tmp->dir = vec_arr + 1;
	tmp->plane = vec_arr + 2;
	tmp->ray = vec_arr + 3;
	tmp->pos->x = info->map->pos.x + 0.5;
	tmp->pos->y = info->map->pos.y + 0.5l;
	init_vector(info, info->map->player_dir);
	tmp->map = coor_arr + 0;
	tmp->step = coor_arr + 1;
}

static void	init_mlx_data(t_info *info)
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
}

static void	init_map_data(t_info *info, char *file, int *map_size)
{
	char	*line;
	int		fd;
	int		elem_cnt;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		print_error(sys_call, __func__, __LINE__);
	info->map->width = map_size[X];
	info->map->height = map_size[Y];
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
		print_error(sys_call, __func__, __LINE__);
}

t_info	*init_info(char *file, int *map_size)
{
	t_info	*info;

	info = ft_calloc(1, sizeof(t_info));
	if (!info)
		print_error(sys_call, __func__, __LINE__);
	info->map = ft_calloc(1, sizeof(t_map));
	info->texture = ft_calloc(1, sizeof(t_tex));
	info->screen = ft_calloc(1, sizeof(t_img));
	info->calc = ft_calloc(1, sizeof(t_data));
	if (!info->map || !info->texture || !info->screen || !info->calc)
		print_error(sys_call, __func__, __LINE__);
	init_mlx_data(info);
	init_map_data(info, file, map_size);
	if (is_map_valid(info->map) == false)
		print_error(map_data, __func__, __LINE__);
	init_calc(info);
	return (info);
}
