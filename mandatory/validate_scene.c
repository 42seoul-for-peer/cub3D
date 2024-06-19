/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_scene.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeunkim <hyeunkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 15:39:12 by hyeunkim          #+#    #+#             */
/*   Updated: 2024/06/19 15:39:53 by hyeunkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	is_surrounded(t_map *map, int x, int y)
{
	char	elem_up;
	char	elem_down;
	char	elem_left;
	char	elem_right;

	if (y == 0 || y == map->height - 1)
		return (false);
	if (x == 0 || x == map->width - 1)
		return (false);
	elem_up = map->scene[y - 1][x];
	elem_down = map->scene[y + 1][x];
	elem_left = map->scene[y][x + 1];
	elem_right = map->scene[y][x - 1];
	if (elem_up == 0 || elem_down == 0 || elem_right == 0 || elem_left == 0)
		return (false);
	if (elem_up == ' ' || elem_down == ' ' || \
			elem_right == ' ' || elem_left == ' ')
		return (false);
	return (true);
}

bool	is_map_valid(t_map *map)
{
	char	elem;
	int		x;
	int		y;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width && map->scene[y][x])
		{
			elem = map->scene[y][x];
			if (elem == 'N' || elem == 'S' || elem == 'W' || elem == 'E')
			{
				map->pos.x = x;
				map->pos.y = y;
				map->player_dir = elem;
				map->scene[y][x] = 'P';
			}
			else if (elem != ' ' && elem != '1' && !is_surrounded(map, x, y))
				return (false);
			x++;
		}
		y++;
	}
	return (true);
}
