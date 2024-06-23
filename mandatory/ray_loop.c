/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_loop.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeunkim <hyeunkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 14:56:14 by seungjun          #+#    #+#             */
/*   Updated: 2024/06/23 19:53:10 by hyeunkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#include <stdio.h>
void	raycasting_loop(t_info *info)
{
	double	cam_x;
	int		screen_width;
	t_data	*tmp;

	screen_width = 0;
	while (screen_width < WIN_WIDTH)
	{
		cam_x = screen_width * 2 / (double) WIN_WIDTH - 1;
		calc(info, info->calc, cam_x);
		tmp = info->calc;
		printf("screen %4d pos(%f, %f), map(%d, %d)\n", screen_width, tmp->pos->x, tmp->pos->y, tmp->map->x, tmp->map->y);
		draw(info, screen_width);
		screen_width++;
	}
	printf("------------------------------------------------------------------------\n");
	mlx_put_image_to_window(info->mlx, info->win, info->screen->ptr, 0, 0);
}
