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

# define MOVE_SPEED 0.1
# define ROT_SPEED 0.2


int dev_close(int key, void *tmp) //mlx key hook (ESC)
{
	(void)tmp;
	if (key == 53)
		exit(0);
	return (0);
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
		dev_close(53, 0);
    else if (key == KEY_W)
    {
        if (map->scene[(int) calc->pos->y][(int) (calc->pos->x + calc->dir->x * MOVE_SPEED)] != '1')
            calc->pos->x += calc->dir->x * MOVE_SPEED;
        if (map->scene[(int) (calc->pos->y + calc->dir->y * MOVE_SPEED)][(int) calc->pos->x] != '1')
            calc->pos->y += calc->dir->y * MOVE_SPEED;
    }
    else if (key == KEY_S)
    {
        if (map->scene[(int) calc->pos->y][(int) (calc->pos->x - calc->dir->x * MOVE_SPEED)] != '1')
            calc->pos->x -= calc->dir->x * MOVE_SPEED;
        if (map->scene[(int) (calc->pos->y - calc->dir->y * MOVE_SPEED)][(int) calc->pos->x] != '1')
            calc->pos->y -= calc->dir->y * MOVE_SPEED;
    }
    else if (key == KEY_A)
    {
        if (map->scene[(int) (calc->pos->y)][(int) (calc->pos->x + calc->dir->y * MOVE_SPEED)] != '1')
            calc->pos->x += calc->dir->y * MOVE_SPEED;
        if (map->scene[(int) (calc->pos->y - calc->dir->x * MOVE_SPEED)][(int) (calc->pos->x)] != '1')
            calc->pos->y -= calc->dir->x * MOVE_SPEED;
    }
    else if (key == KEY_D)
    {
        if (map->scene[(int) (calc->pos->y)][(int) (calc->pos->x - calc->dir->y * MOVE_SPEED)] != '1')
		    calc->pos->x -= calc->dir->y * MOVE_SPEED;
        if (map->scene[(int) (calc->pos->y + calc->dir->x * MOVE_SPEED)][(int) (calc->pos->x)] != '1')
            calc->pos->y += calc->dir->x * MOVE_SPEED;
    }
    else if (key == KEY_LEFT)
    {
        double old_dir_x = calc->dir->x;
        calc->dir->x = calc->dir->x * cos(-ROT_SPEED) - calc->dir->y * sin(-ROT_SPEED);
        calc->dir->y = old_dir_x * sin(-ROT_SPEED) + calc->dir->y * cos(-ROT_SPEED);
        double oldPlaneX = calc->plane->x;
        calc->plane->x = calc->plane->x * cos(-ROT_SPEED) - calc->plane->y * sin(-ROT_SPEED);
        calc->plane->y = oldPlaneX * sin(-ROT_SPEED) + calc->plane->y * cos(-ROT_SPEED);
    }
    else if (key == KEY_RIGHT)
    {
        double old_dir_x = calc->dir->x;
        calc->dir->x = calc->dir->x * cos(ROT_SPEED) - calc->dir->y * sin(ROT_SPEED);
        calc->dir->y = old_dir_x * sin(ROT_SPEED) + calc->dir->y * cos(ROT_SPEED);
        double oldPlaneX = calc->plane->x;
        calc->plane->x = calc->plane->x * cos(ROT_SPEED) - calc->plane->y * sin(ROT_SPEED);
        calc->plane->y = oldPlaneX * sin(ROT_SPEED) + calc->plane->y * cos(ROT_SPEED);
    }
	raycasting_loop(info);
	return (0);
}

void	raycasting_loop(t_info *info)
{
	double	cam_x;
    int     screen_width;

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
