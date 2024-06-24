/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeunkim <hyeunkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 12:52:39 by hyeunkim          #+#    #+#             */
/*   Updated: 2024/06/24 19:16:43 by hyeunkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	set_dist(t_ray *ray)
{
	ray->delta[X] = fabs(1 / ray->ray_dir->x);
	ray->delta[Y] = fabs(1 / ray->ray_dir->y);
	if (ray->ray_dir->x < 0)
	{
		ray->step->x = -1;
		ray->side[X] = (ray->pl_pos->x - ray->map->x) * ray->delta[X];
	}
	else
	{
		ray->step->x = 1;
		ray->side[X] = (ray->map->x + 1.0 - ray->pl_pos->x) * ray->delta[X];
	}
	if (ray->ray_dir->y < 0)
	{
		ray->step->y = -1;
		ray->side[Y] = (ray->pl_pos->y - ray->map->y) * ray->delta[Y];
	}
	else
	{
		ray->step->y = 1;
		ray->side[Y] = (ray->map->y + 1.0 - ray->pl_pos->y) * ray->delta[Y];
	}
}

static int	hit_loop(t_info *info, t_ray *ray)
{
	int		side;
	bool	hit;

	hit = false;
	while (hit == false)
	{
		if (ray->side[X] < ray->side[Y])
		{
			ray->side[X] += ray->delta[X];
			ray->map->x += ray->step->x;
			side = X;
		}
		else
		{
			ray->side[Y] += ray->delta[Y];
			ray->map->y += ray->step->y;
			side = Y;
		}
		if (info->map->scene[ray->map->y][ray->map->x] == '1')
			hit = true;
	}
	return (side);
}

static double	get_perp_wall_dist(t_ray *ray)
{
	t_coor	*map;
	t_coor	*step;
	t_vec	*pl_pos;
	t_vec	*ray_dir;
	double	res;

	map = ray->map;
	step = ray->step;
	pl_pos = ray->pl_pos;
	ray_dir = ray->ray_dir;
	if (ray->hit_side == X)
		res = \
			(map->x - pl_pos->x + (1 - step->x) / 2) / ray_dir->x;
	else
		res = \
			(map->y - pl_pos->y + (1 - step->y) / 2) / ray_dir->y;
	return (res);
}

void	calc(t_info *info, t_ray *ray, int scr_x)
{
	double	cam_x;

	cam_x = scr_x * 2 / (double) WIN_W - 1;
	ray->ray_dir->x = ray->pl_dir->x + ray->plane->x * cam_x;
	ray->ray_dir->y = ray->pl_dir->y + ray->plane->y * cam_x;
	ray->map->x = (int) ray->pl_pos->x;
	ray->map->y = (int) ray->pl_pos->y;
	set_dist(ray);
	ray->hit_side = hit_loop(info, ray);
	ray->perp_wall_dist = get_perp_wall_dist(ray);
	ray->line_len = (int)(WIN_H / ray->perp_wall_dist);
}
