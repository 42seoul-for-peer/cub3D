/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_loop.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeunkim <hyeunkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 14:56:14 by seungjun          #+#    #+#             */
/*   Updated: 2024/06/24 17:38:05 by hyeunkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	raycasting_loop(t_info *info)
{
	int		screen_x;

	screen_x = 0;
	while (screen_x < WIN_WIDTH)
	{
		calc(info, info->calc, screen_x);
		draw(info, screen_x);
		screen_x++;
	}
	mlx_put_image_to_window(info->mlx, info->win, info->screen->ptr, 0, 0);
}
