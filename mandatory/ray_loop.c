/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_loop.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeunkim <hyeunkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 14:56:14 by seungjun          #+#    #+#             */
/*   Updated: 2024/06/24 21:12:15 by hyeunkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	raycasting_loop(t_info *info)
{
	int		scr_x;

	scr_x = 0;
	while (scr_x < WIN_W)
	{
		calc(info, info->ray, scr_x);
		draw(info, scr_x);
		scr_x++;
	}
	mlx_put_image_to_window(info->mlx, info->win, info->scr->ptr, 0, 0);
}
