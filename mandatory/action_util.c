/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeunkim <hyeunkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 21:29:55 by hyeunkim          #+#    #+#             */
/*   Updated: 2024/06/24 21:30:21 by hyeunkim         ###   ########.fr       */
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

bool	check_wall(t_map *map, t_vec target)
{
	char	elem;

	if (target.x < 0 || target.y < 0 || \
		target.x > map->w - 1 || target.y > map->h - 1)
		return (true);
	elem = map->scene[(int)target.y][(int)target.x];
	if (elem == '1' || elem == '0')
		return (true);
	return (false);
}
