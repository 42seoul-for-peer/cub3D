/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeunkim <hyeunkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 14:56:14 by seungjun          #+#    #+#             */
/*   Updated: 2024/06/24 19:15:07 by hyeunkim         ###   ########.fr       */
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

bool	is_movable(t_map *map, t_vec *pos, double delta, int dir_flag)
{
	t_vec	target;

	target.x = pos->x;
	target.y = pos->y;
	if (dir_flag == X)
		target.x += delta;
	else
		target.y += delta;
	if (target.x < 0 || target.x > map->w - 1 || \
		target.y < 0 || target.y > map->h - 1)
		return (false);
	if (map->scene[(int)target.y][(int)target.x] == '1' || \
		map->scene[(int)target.y][(int)target.x] == ' ')
		return (false);
	if (dir_flag == X)
		target.x += delta * 0.000001;
	else
		target.y += delta * 0.000001;
	if (target.x < 0 || target.x > map->w - 1 || \
		target.y < 0 || target.y > map->h - 1)
		return (false);
	if (map->scene[(int)target.y][(int)target.x] == '1' || \
		map->scene[(int)target.y][(int)target.x] == ' ')
		return (false);
	return (true);
}

void	action_move(int key, t_ray *ray, t_map *map)
{
	double	move_x;
	double	move_y;

	if (key == KEY_W || key == KEY_S)
	{
		move_x = ray->pl_dir->x;
		move_y = ray->pl_dir->y;
	}
	else
	{
		move_x = ray->pl_dir->y;
		move_y = ray->pl_dir->x;
	}
	if (key == KEY_S || key == KEY_D)
		move_x *= -1;
	if (key == KEY_S || key == KEY_A)
		move_y *= -1;
	move_x *= MOVE_SPEED;
	move_y *= MOVE_SPEED;
	if (is_movable(map, ray->pl_pos, move_x, X))
		ray->pl_pos->x += move_x;
	if (is_movable(map, ray->pl_pos, move_y, Y))
		ray->pl_pos->y += move_y;
}

int	key_press(int key, void	*tmp)
{
	t_info	*info;
	t_ray	*ray;
	t_map	*map;

	info = tmp;
	ray = info->ray;
	map = info->map;
	if (key == KEY_ESC)
		close_mlx();
	else if (key == KEY_W || key == KEY_A || key == KEY_S || key == KEY_D)
		action_move(key, ray, map);
	else if (key == KEY_LEFT || key == KEY_RIGHT)
		action_rotate(key, ray->pl_dir, ray->plane);
	raycasting_loop(info);
	return (0);
}
