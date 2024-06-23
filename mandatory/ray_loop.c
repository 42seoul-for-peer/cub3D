/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_loop.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeunkim <hyeunkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 14:56:14 by seungjun          #+#    #+#             */
/*   Updated: 2024/06/20 19:00:51 by hyeunkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	raycasting_loop(t_info *info)
{
	double	cam_x;
	int		screen_width;

	screen_width = 0;
	while (screen_width < WIN_WIDTH)
	{
		cam_x = screen_width * 2 / (double) WIN_WIDTH - 1;
		calc(info, info->calc, cam_x);
		draw(info, screen_width);
		screen_width++;
	}
	mlx_put_image_to_window(info->mlx, info->win, info->screen->ptr, 0, 0);
}
