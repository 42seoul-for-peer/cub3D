/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeunkim <hyeunkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 12:52:39 by hyeunkim          #+#    #+#             */
/*   Updated: 2024/06/23 14:33:17 by hyeunkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_dist(t_data *calc)
{
	calc->delta_dist[X] = fabs(1 / calc->ray->x);
	calc->delta_dist[Y] = fabs(1 / calc->ray->y);
	if (calc->ray->x < 0)
	{
		calc->step->x = -1;
		calc->side_dist[X] = (calc->pos->x - calc->map->x) * calc->delta_dist[X];
	}
	else
	{
		calc->step->x = 1;
		calc->side_dist[X] = (calc->map->x + 1.0 - calc->pos->x) * calc->delta_dist[X];
	}
	if (calc->ray->y < 0)
	{
		calc->step->y = -1;
		calc->side_dist[Y] = (calc->pos->y - calc->map->y) * calc->delta_dist[Y];
	}
	else
	{
		calc->step->y = 1;
		calc->side_dist[Y] = (calc->map->y + 1.0 - calc->pos->y) * calc->delta_dist[Y];
	}
}

int	hit_loop(t_info *info, t_data *calc)
{
	int		side;
	bool	hit;

	hit = false;
	while (hit == false)
	{
		if (calc->side_dist[X] < calc->side_dist[Y])
		{
			calc->side_dist[X] += calc->delta_dist[X];
			calc->map->x += calc->step->x;
			side = X;
		}
		else
		{
			calc->side_dist[Y] += calc->delta_dist[Y];
			calc->map->y += calc->step->y;
			side = Y;
		}
		if (info->map->scene[calc->map->y][calc->map->x] == '1')
			hit = true;
	}
	return (side);
}
#include <stdio.h>
void	calc(t_info *info, t_data *calc, double cam_x)
{
	calc->ray->x = calc->dir->x + calc->plane->x * cam_x;
	calc->ray->y = calc->dir->y + calc->plane->y * cam_x;
	calc->map->x = calc->pos->x;
	calc->map->y = calc->pos->y;
	set_dist(info->calc);
	calc->side = hit_loop(info, info->calc);
	if (calc->side == X)
		calc->perp_wall_dist = (calc->map->x - calc->pos->x + (1 - calc->step->x) / 2) / calc->ray->x;
	else
		calc->perp_wall_dist = (calc->map->y - calc->pos->y + (1 - calc->step->y) / 2) / calc->ray->y;
	// if (calc->perp_wall_dist < 0.01)
	// 	calc->line_height = (int) (WIN_HEIGHT / 0.01);
	// else
	// 	calc->line_height = (int) (WIN_HEIGHT / calc->perp_wall_dist);
	calc->line_height = (int) (WIN_HEIGHT / calc->perp_wall_dist);
	// printf("map (%d, %d) pos (%f, %f) ", calc->map->x, calc->map->y, calc->pos->x, calc->pos->y);
	// printf("step (%d %d) ",  calc->step->x, calc->step->y);
	// printf("ray (%f, %f)\n", calc->ray->x, calc->ray->y);
	// printf("1 - step / 2: (%d, %d)\n", (1 - calc->step->x) / 2, (1 - calc->step->x) / 2);
	// printf("map - pos + (1 - step) /2: (%f, %f)\n", calc->map->x - calc->pos->x + (1 - calc->step->x), calc->map->y - calc->pos->y + (1 - calc->step->y) / 2);
	// if (calc->side == X)
	// 	printf("->x perp %f\n", (calc->map->x - calc->pos->x + (1 - calc->step->x) / 2) / calc->ray->x);
	// else
	// 	printf("->y perp %f\n", (calc->map->y - calc->pos->y + (1 - calc->step->y) / 2) / calc->ray->y);
	// printf("-------------\n");
}
