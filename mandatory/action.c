/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeunkim <hyeunkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 14:56:14 by seungjun          #+#    #+#             */
/*   Updated: 2024/06/23 15:44:01 by hyeunkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "cub3d.h"

int	dev_close(int key, void *tmp)
{
	(void)tmp;
	if (key == 53)
		exit(0);
	return (0);
}

void	action_rotate(int key, t_vec *dir, t_vec *plane)
{
	double	old_plane_x;
	double	old_dir_x;

	old_plane_x = plane->x;
	old_dir_x = dir->x;
	if (key == KEY_LEFT)
	{
		dir->x = dir->x * cos(-ROT_SPEED) - dir->y * sin(-ROT_SPEED);
		dir->y = old_dir_x * sin(-ROT_SPEED) + dir->y * cos(-ROT_SPEED);
		plane->x = plane->x * cos(-ROT_SPEED) - plane->y * sin(-ROT_SPEED);
		plane->y = old_plane_x * sin(-ROT_SPEED) + plane->y * cos(-ROT_SPEED);
	}
	else if (key == KEY_RIGHT)
	{
		dir->x = dir->x * cos(ROT_SPEED) - dir->y * sin(ROT_SPEED);
		dir->y = old_dir_x * sin(ROT_SPEED) + dir->y * cos(ROT_SPEED);
		plane->x = plane->x * cos(ROT_SPEED) - plane->y * sin(ROT_SPEED);
		plane->y = old_plane_x * sin(ROT_SPEED) + plane->y * cos(ROT_SPEED);
	}
}

int	get_edge_pos(double num)
{
	double	test;

	test = num;
	while (test < 1)
		test -= 1;
	printf("test : %f\n", test);
	if (1 - MOVE_SPEED <= test && test < 1)
		return (ceil(num));
	else if (0 <= test && test <= MOVE_SPEED)
		return (floor(num));
	else
		return (num);
}

void	action_move(int key, t_data *calc, char **scene)
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
	printf("| before position x, y : (%.10f, %.10f)\n", calc->pos->x, calc->pos->y);
	// if (scene[(int)calc->pos->y][(int)(calc->pos->x + move_x)] != '1')
	// 	calc->pos->x += move_x;
	// if (scene[(int)(calc->pos->y + move_y)][(int)calc->pos->x] != '1')
	// 	calc->pos->y += move_y;
	if (scene[(int)calc->pos->y][(int)(get_edge_pos(calc->pos->x + move_x))] != '1')
		calc->pos->x += move_x;
	if (scene[(int)(get_edge_pos(calc->pos->y + move_y))][(int)calc->pos->x] != '1')
		calc->pos->y += move_y;
	printf("| after position x, y : (%.10f, %.10f)\n\n", calc->pos->x, calc->pos->y);
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
		dev_close(key, 0);
	else if (key == KEY_W || key == KEY_A || key == KEY_S || key == KEY_D)
		action_move(key, calc, map->scene);
	else if (key == KEY_LEFT || key == KEY_RIGHT)
		action_rotate(key, calc->dir, calc->plane);
	raycasting_loop(info);
	return (0);
}
