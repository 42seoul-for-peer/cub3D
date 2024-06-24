/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeunkim <hyeunkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 14:56:14 by seungjun          #+#    #+#             */
/*   Updated: 2024/06/24 14:15:23 by hyeunkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	close_mlx(void)
{
	exit(EXIT_SUCCESS);
}

void	action_rotate(int key, t_vec *dir, t_vec *plane)
{
	double	old_plane_x;
	double	old_dir_x;
	double	rad;

	rad = ROT_ANGLE * acos(-1) / 180;
	old_plane_x = plane->x;
	old_dir_x = dir->x;
	if (key == KEY_LEFT)
	{
		dir->x = dir->x * cos(-rad) - dir->y * sin(-rad);
		dir->y = old_dir_x * sin(-rad) + dir->y * cos(-rad);
		plane->x = plane->x * cos(-rad) - plane->y * sin(-rad);
		plane->y = old_plane_x * sin(-rad) + plane->y * cos(-rad);
	}
	else if (key == KEY_RIGHT)
	{
		dir->x = dir->x * cos(rad) - dir->y * sin(rad);
		dir->y = old_dir_x * sin(rad) + dir->y * cos(rad);
		plane->x = plane->x * cos(rad) - plane->y * sin(rad);
		plane->y = old_plane_x * sin(rad) + plane->y * cos(rad);
	}
}

bool	is_movable(t_map *map, double target_x, double target_y)
{
	if (floor(target_x) != floor(target_x + 0.000001))
		target_x = ceil(target_x);
	if (floor(target_y) != floor(target_y + 0.000001))
		target_y = ceil(target_y);
	if (target_x > map->width - 1 || target_y > map->height - 1)
		return (false);
	if (map->scene[(int)target_y][(int)target_x] == '1')
		return (false);
	if (map->scene[(int)target_y][(int)target_x] == ' ')
		return (false);
	return (true);
}

void	action_move(int key, t_data *calc, t_map *map)
{
	double	move_x;
	double	move_y;

	if (key == KEY_W || key == KEY_S)
	{
		move_x = calc->dir->x;
		move_y = calc->dir->y;
	}
	else
	{
		move_x = calc->dir->y;
		move_y = calc->dir->x;
	}
	if (key == KEY_S || key == KEY_D)
		move_x *= -1;
	if (key == KEY_S || key == KEY_A)
		move_y *= -1;
	move_x *= MOVE_SPEED;
	move_y *= MOVE_SPEED;
	if (is_movable(map, calc->pos->x + move_x, calc->pos->y))
		calc->pos->x += move_x;
	if (is_movable(map, calc->pos->x, calc->pos->y + move_y))
		calc->pos->y += move_y;
}

int	key_press(int key, void	*tmp)
{
	t_info	*info;
	t_data	*calc;
	t_map	*map;

	info = tmp;
	calc = info->calc;
	map = info->map;
	if (key == KEY_ESC)
		close_mlx();
	else if (key == KEY_W || key == KEY_A || key == KEY_S || key == KEY_D)
		action_move(key, calc, map);
	else if (key == KEY_LEFT || key == KEY_RIGHT)
		action_rotate(key, calc->dir, calc->plane);
	raycasting_loop(info);
	return (0);
}
