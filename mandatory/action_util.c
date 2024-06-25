/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeunkim <hyeunkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 21:29:55 by hyeunkim          #+#    #+#             */
/*   Updated: 2024/06/25 13:50:16 by hyeunkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	adjust_double(double target)
{
	if ((int)target != (int)(target + 0.000001))
		target += 0.000001;
	else if ((int)target != (int)(target - 0.000001))
		target -= 0.000001;
	return (target);
}

bool	is_wall(t_map *map, double target_x, double target_y)
{
	char	elem;

	if (target_x < 0 || target_y < 0 || \
		target_x > map->w - 1 || target_y > map->h - 1)
		return (true);
	elem = map->scene[(int)target_y][(int)target_x];
	if (elem == '1')
		return (true);
	return (false);
}
