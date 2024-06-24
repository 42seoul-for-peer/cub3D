/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_loop.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeunkim <hyeunkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 14:56:14 by seungjun          #+#    #+#             */
/*   Updated: 2024/06/24 15:11:52 by hyeunkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	raycasting_loop(t_info *info)
{
	t_data	*calc;
	double	cam_x;
	int		screen_width;

	calc = info->calc;
	screen_width = 0;
	while (screen_width < WIN_WIDTH)
	{
		cam_x = screen_width * 2 / (double) WIN_WIDTH - 1;
		calc->ray->x = calc->dir->x + calc->plane->x * cam_x;
		calc->ray->y = calc->dir->y + calc->plane->y * cam_x;
		calc->map->x = (int) calc->pos->x;
		calc->map->y = (int) calc->pos->y;
		calculator(info, info->calc);
		draw(info, screen_width);
		screen_width++;
	}
	mlx_put_image_to_window(info->mlx, info->win, info->screen->ptr, 0, 0);
}
