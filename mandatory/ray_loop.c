/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_loop.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeunkim <hyeunkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 14:56:14 by seungjun          #+#    #+#             */
/*   Updated: 2024/06/24 15:34:47 by hyeunkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	raycasting_loop(t_info *info)
{
	t_data	*calc;
	double	cam_x;
	int		screen_x;

	calc = info->calc;
	screen_x = 0;
	while (screen_x < WIN_WIDTH)
	{
		cam_x = screen_x * 2 / (double) WIN_WIDTH - 1;
		calc->ray->x = calc->dir->x + calc->plane->x * cam_x;
		calc->ray->y = calc->dir->y + calc->plane->y * cam_x;
		calc->map->x = (int) calc->pos->x;
		calc->map->y = (int) calc->pos->y;
		calculator(info, info->calc);
		draw(info, screen_x);
		screen_x++;
	}
	mlx_put_image_to_window(info->mlx, info->win, info->screen->ptr, 0, 0);
}
