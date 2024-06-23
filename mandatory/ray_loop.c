/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_loop.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeunkim <hyeunkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 14:56:14 by seungjun          #+#    #+#             */
/*   Updated: 2024/06/22 19:38:58 by hyeunkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

# define MOVE_SPEED 0.1
# define ROT_SPEED 1.5


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
	double	rad;

	info = tmp;
	calc = info->calc;
	map = info->map;
	rad = ROT_SPEED * acos(-1) / 180;
	ft_printf("(%d, %d)", (int)calc->pos->x, (int)calc->pos->y);
	if (key == KEY_ESC)
		dev_close(53, 0);
    else if (key == KEY_W)
    {
		ft_printf("->(%d, %d)\n", (int)(calc->pos->x + calc->dir->x * MOVE_SPEED), (int)(calc->pos->y + calc->dir->y * MOVE_SPEED));
        if (map->scene[(int) calc->pos->y][(int) (calc->pos->x + calc->dir->x * MOVE_SPEED)] != '1')
            calc->pos->x += calc->dir->x * MOVE_SPEED;
        if (map->scene[(int) (calc->pos->y + calc->dir->y * MOVE_SPEED)][(int) calc->pos->x] != '1')
            calc->pos->y += calc->dir->y * MOVE_SPEED;
    }
    else if (key == KEY_S)
    {
		ft_printf("->(%d, %d)\n", (int)(calc->pos->x + calc->dir->x * MOVE_SPEED), (int)(calc->pos->y + calc->dir->y * MOVE_SPEED));
        if (map->scene[(int) calc->pos->y][(int) (calc->pos->x - calc->dir->x * MOVE_SPEED)] != '1')
            calc->pos->x -= calc->dir->x * MOVE_SPEED;
        if (map->scene[(int) (calc->pos->y - calc->dir->y * MOVE_SPEED)][(int) calc->pos->x] != '1')
            calc->pos->y -= calc->dir->y * MOVE_SPEED;
    }
    else if (key == KEY_A)
    {
		ft_printf("->(%d, %d)\n", (int)(calc->pos->x + calc->dir->x * MOVE_SPEED), (int)(calc->pos->y + calc->dir->y * MOVE_SPEED));
        if (map->scene[(int) (calc->pos->y)][(int) (calc->pos->x + calc->dir->y * MOVE_SPEED)] != '1')
            calc->pos->x += calc->dir->y * MOVE_SPEED;
        if (map->scene[(int) (calc->pos->y - calc->dir->x * MOVE_SPEED)][(int) (calc->pos->x)] != '1')
            calc->pos->y -= calc->dir->x * MOVE_SPEED;
    }
    else if (key == KEY_D)
    {
		ft_printf("->(%d, %d)\n", (int)(calc->pos->x + calc->dir->x * MOVE_SPEED), (int)(calc->pos->y + calc->dir->y * MOVE_SPEED));
        if (map->scene[(int) (calc->pos->y)][(int) (calc->pos->x - calc->dir->y * MOVE_SPEED)] != '1')
		    calc->pos->x -= calc->dir->y * MOVE_SPEED;
        if (map->scene[(int) (calc->pos->y + calc->dir->x * MOVE_SPEED)][(int) (calc->pos->x)] != '1')
            calc->pos->y += calc->dir->x * MOVE_SPEED;
    }
    else if (key == KEY_LEFT)
    {
        double old_dir_x = calc->dir->x;
        calc->dir->x = calc->dir->x * cos(-rad) - calc->dir->y * sin(-rad);
        calc->dir->y = old_dir_x * sin(-rad) + calc->dir->y * cos(-rad);
        double oldPlaneX = calc->plane->x;
        calc->plane->x = calc->plane->x * cos(-rad) - calc->plane->y * sin(-rad);
        calc->plane->y = oldPlaneX * sin(-rad) + calc->plane->y * cos(-rad);
    }
    else if (key == KEY_RIGHT)
    {
        double old_dir_x = calc->dir->x;
        calc->dir->x = calc->dir->x * cos(rad) - calc->dir->y * sin(rad);
        calc->dir->y = old_dir_x * sin(rad) + calc->dir->y * cos(rad);
        double oldPlaneX = calc->plane->x;
        calc->plane->x = calc->plane->x * cos(rad) - calc->plane->y * sin(rad);
        calc->plane->y = oldPlaneX * sin(rad) + calc->plane->y * cos(rad);
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
