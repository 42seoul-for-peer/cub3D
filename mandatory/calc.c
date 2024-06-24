/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeunkim <hyeunkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 12:52:39 by hyeunkim          #+#    #+#             */
/*   Updated: 2024/06/24 15:12:30 by hyeunkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	set_dist(t_data *calc)
{
	calc->delta[X] = fabs(1 / calc->ray->x);
	calc->delta[Y] = fabs(1 / calc->ray->y);
	if (calc->ray->x < 0)
	{
		calc->step->x = -1;
		calc->side[X] = (calc->pos->x - calc->map->x) * calc->delta[X];
	}
	else
	{
		calc->step->x = 1;
		calc->side[X] = (calc->map->x + 1.0 - calc->pos->x) * calc->delta[X];
	}
	if (calc->ray->y < 0)
	{
		calc->step->y = -1;
		calc->side[Y] = (calc->pos->y - calc->map->y) * calc->delta[Y];
	}
	else
	{
		calc->step->y = 1;
		calc->side[Y] = (calc->map->y + 1.0 - calc->pos->y) * calc->delta[Y];
	}
}

static int	hit_loop(t_info *info, t_data *calc)
{
	int		side;
	bool	hit;

	hit = false;
	while (hit == false)
	{
		if (calc->side[X] < calc->side[Y])
		{
			calc->side[X] += calc->delta[X];
			calc->map->x += calc->step->x;
			side = X;
		}
		else
		{
			calc->side[Y] += calc->delta[Y];
			calc->map->y += calc->step->y;
			side = Y;
		}
		if (info->map->scene[calc->map->y][calc->map->x] == '1')
			hit = true;
	}
	return (side);
}

void	calculator(t_info *info, t_data *calc)
{
	set_dist(info->calc);
	calc->hit_side = hit_loop(info, info->calc);
	if (calc->hit_side == X)
		calc->perp_wall_dist = \
			(calc->map->x - calc->pos->x + (1 - calc->step->x) / 2) / calc->ray->x;
	else
		calc->perp_wall_dist = \
			(calc->map->y - calc->pos->y + (1 - calc->step->y) / 2) / calc->ray->y;
	calc->line_height = (int)(WIN_HEIGHT / calc->perp_wall_dist);
}
