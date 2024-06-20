/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_loop.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeunkim <hyeunkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 14:56:14 by seungjun          #+#    #+#             */
/*   Updated: 2024/06/20 16:10:37 by hyeunkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>

# define MOVE_SPEED 1

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
    if (key == KEY_W)
    {
        if(map->scene[(int) calc->pos->y][(int) (calc->pos->x + calc->dir->x * MOVE_SPEED)] != '1')
            calc->pos->x += calc->dir->x * MOVE_SPEED;
        if(map->scene[(int) (calc->pos->y + calc->dir->y * MOVE_SPEED)][(int) calc->pos->x] != '1')
            calc->pos->y += calc->dir->y * MOVE_SPEED;
    }
    // else if (key == KEY_S)
    // {

    // }
    // else if (key == KEY_A)
    // {

    // }
    // else if (key == KEY_D)
    // {
        
    // }
	raycasting_loop(info);
    return (0);
    /* 이동하기 위해 필요한 변수
    map, posX, posY, dirX, dirY, moveSpeed, rotSpeed, planeX, planeY

    if (keyDown(SDLK_UP))
    {
        if(worldMap[int(posX + dirX * moveSpeed)][int(posY)] == false) posX += dirX * moveSpeed;
        if(worldMap[int(posX)][int(posY + dirY * moveSpeed)] == false) posY += dirY * moveSpeed;
    }
    //move backwards if no wall behind you
    if (keyDown(SDLK_DOWN))
    {
        if(worldMap[int(posX - dirX * moveSpeed)][int(posY)] == false) posX -= dirX * moveSpeed;
        if(worldMap[int(posX)][int(posY - dirY * moveSpeed)] == false) posY -= dirY * moveSpeed;
    }
    //rotate to the right
    if (keyDown(SDLK_RIGHT))
    {
      //both camera direction and camera plane must be rotated
        double oldDirX = dirX;
        dirX = dirX * cos(-rotSpeed) - dirY * sin(-rotSpeed);
        dirY = oldDirX * sin(-rotSpeed) + dirY * cos(-rotSpeed);
        double oldPlaneX = planeX;
        planeX = planeX * cos(-rotSpeed) - planeY * sin(-rotSpeed);
        planeY = oldPlaneX * sin(-rotSpeed) + planeY * cos(-rotSpeed);
    }
    //rotate to the left
    if (keyDown(SDLK_LEFT))
    {
        //both camera direction and camera plane must be rotated
        double oldDirX = dirX;
        dirX = dirX * cos(rotSpeed) - dirY * sin(rotSpeed);
        dirY = oldDirX * sin(rotSpeed) + dirY * cos(rotSpeed);
        double oldPlaneX = planeX;
        planeX = planeX * cos(rotSpeed) - planeY * sin(rotSpeed);
        planeY = oldPlaneX * sin(rotSpeed) + planeY * cos(rotSpeed);
    }
    */
	// tutorial(info);
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
}
