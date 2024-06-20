/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeunkim <hyeunkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 12:52:39 by hyeunkim          #+#    #+#             */
/*   Updated: 2024/06/20 15:53:21 by hyeunkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_dist(t_data *calc)
{
	calc->delta_dist->x = fabs(1 / calc->ray->x);
	calc->delta_dist->y = fabs(1 / calc->ray->y);
	if (calc->ray->x < 0)
	{
		calc->step->x = -1;
		calc->side_dist->x = (calc->pos->x - calc->map->x) * calc->delta_dist->x;
	}
	else
	{
		calc->step->x = 1;
		calc->side_dist->x = (calc->map->x + 1.0 - calc->pos->x) * calc->delta_dist->x;
	}
	if (calc->ray->y < 0)
	{
		calc->step->y = -1;
		calc->side_dist->y = (calc->pos->y - calc->map->y) * calc->delta_dist->y;
	}
	else
	{
		calc->step->y = 1;
		calc->side_dist->y = (calc->map->y + 1.0 - calc->pos->y) * calc->delta_dist->y;
	}
}

int	hit_loop(t_info *info, t_data *calc)
{
	int		side;
	bool	hit;

	hit = false;
	while (hit == false)
	{
		if (calc->side_dist->x < calc->side_dist->y)
		{
			calc->side_dist->x += calc->delta_dist->x;
			calc->map->x += calc->step->x;
			side = X;
		}
		else
		{
			calc->side_dist->y += calc->delta_dist->y;
			calc->map->y += calc->step->y;
			side = Y;
		}
		if (info->map->scene[calc->map->y][calc->map->x] == '1')
			hit = true;
	}
	return (side);
}

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
	calc->line_height = (int) (WIN_HEIGHT / calc->perp_wall_dist);
}