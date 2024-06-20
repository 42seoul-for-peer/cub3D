/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   .raycasting_tutorial_old.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeunkim <hyeunkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 14:56:14 by seungjun          #+#    #+#             */
/*   Updated: 2024/06/20 16:58:26 by hyeunkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>

# define MOVE_SPEED 1

int dev_close(int key, void *temp) //mlx key hook (ESC)
{
	temp = 0;
	if (key == 53)
		exit(0);
	return (0);
}

int	key_press(int key, void *tmp)
{
    tmp = 0;
	if (key == KEY_ESC)
		dev_close(53, 0);
    if (key == KEY_W)
    {
		// printf(">tartget: (%f, %f)\n", pos->x + dir->x * MOVE_SPEED, pos->y);
        // if(scene[(int) pos->y][(int) (pos->x + dir->x * MOVE_SPEED)] != '1')
        //     pos->x += dir->x * MOVE_SPEED;
		// printf(">>target: (%f, %f)\n", pos->x, pos->y + dir->y * MOVE_SPEED);
        // if(scene[(int) (pos->y + dir->y * MOVE_SPEED)][(int) pos->x] != '1')
        //     pos->y += dir->y * MOVE_SPEED;
		// printf(">>>position: (%f, %f)\n", pos->x, pos->y);
    }
    else if (key == KEY_S)
    {

    }
    else if (key == KEY_A)
    {

    }
    else if (key == KEY_D)
    {
        
    }
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

void    tutorial_ver2(t_info *info)
{
    t_coor	screen;
	double	cam_x;
    int     screen_width;

	screen_width = 0;
	while (screen_width < WIN_WIDTH)
	{
		cam_x = screen_width * 2 / (double) WIN_WIDTH - 1;
		calc(info, info->calc, &screen, cam_x);
        draw(info, screen_width);
	}
    mlx_hook(info->win, 17, 0, &dev_close, 0);
	mlx_hook(info->win, 2, 0, &key_press, 0);
    mlx_loop(info->mlx);
}

void    tutorial(t_info *info)
{
    // t_vec    *pos;        // 플레이어의 시작 위치
    // t_vec    *dir;        // 초기 방향 벡터
    // t_vec    *plane;      // 플레이어가 바라보는 카메라 평면(출력 화면, 불변)
    // t_vec    raydir;     // 광선의 방향 벡터

    double  cam_x;        // x축 0부터 1920까지 광선을 쏠 때, 그 광선의 카메라 평면 x좌표
    double  side_dist[2];   // [시작점] -> [첫번째 x또는 y면] 까지의 광선 이동거리
    double  delta_dist[2];	// [x면] -> [다음 x면] 또는 [y면] -> [다음 y면] 까지의 광선 이동거리
    double  perpWallDist;   // 광선의 총 이동거리 (수직거리: 카메라 평면하고 나란한 플레이어 평면까지의 거리 )
    double  wallX;          // 벽과 부딪힌 자리의 X좌표
    double  ratio;			// texture 좌표를 얻기 위한 보정 값(비율)
    double  texPos;

	t_coor	screen;			// 출력 화면 상의 위치 (screen.x, screen.y)
	t_coor	map;            // 현재 가리키는 x, y 좌표
    t_coor	tex;	        // 목적하는 texture 파일 상의 좌표
    t_coor	step;			// 광선이 나아가며 변동되는 x축과 y축 int 변화량

    int     side;           // x축 평행 벽에 닿았는지, y축 평행 벽에 닿았는지 판단 인덱스
    int     lineHeight;     // 화면에 그리기 위한 높이
    int     drawStart;      // 화면에 그려기 위한 높이의 start값
    int     drawEnd;        // 화면에 그리기 위한 높이의 end값      (둘이 합하면 화면 출력 높이(height))
    int     color;          // Color값

    bool     hit;           // 벽에 닿았는지 여부 파악

    /*
	dir = init_dir_vector(info->map->player_dir);
    // pos->x = info->map->pos.x + 0.5;
    // pos->y = info->map->pos.y + 0.5;
	--> init.c 로 옮겨짐 */
	// printf("position(%f, %f)\n", info->calc->pos->x, info->calc->pos->y);

    screen.x = 0;
    while (screen.x < 1920)
    {
        /*
        calc_vecs(info, calc);
        */

        cam_x = 2 * screen.x / (double)1920 - 1; //카메라 평면에서의 x좌표
		//화면의 해당 수직선에 닿는 광선의 방향 벡터 (항공뷰)
		info->calc->ray->x = info->calc->dir->x + info->calc->plane->x * cam_x;
		info->calc->ray->y = info->calc->dir->y + info->calc->plane->y * cam_x; 

		//플레이어가 위치한 지도상 격자의 좌표
		/*
        map.x = info->calc->pos->x;
        map.y = info->calc->pos->y;
		--> calc.c: calc_vecs()*/
		/*
        delta_dist[X] = fabs(1 / info->calc->ray->x); //x가 1 증가할 때 광선의 이동 거리
        delta_dist[Y] = fabs(1 / info->calc->ray->y); //y가 1 증가할 때 광선의 이동 거리
        if (info->calc->ray->x < 0) //왼쪽으로 이동하다 처음 만나는 x면까지의 거리
        {
            step.x = -1;
            side_dist[X] = (info->calc->pos->x - map.x) * delta_dist[X];
        }
        else // side_dist[X] : raydir.x> 0인 경우 광선의 시작부터 오른쪽으로 이동하다 처음 만나는 x면까지의 거리
        {
            step.x = 1;
            side_dist[X] = (map.x + 1.0 - info->calc->pos->x) * delta_dist[X];
        }
        if (info->calc->ray->y < 0)
        {
            step.y = -1;
            side_dist[Y] = (info->calc->pos->y - map.y) * delta_dist[Y];
        }
        else
        {
            step.y = 1;
            side_dist[Y] = (map.y + 1.0 - info->calc->pos->y) * delta_dist[Y];
        }
		-->calc.c:set_dist() */
		/*
        hit = false;
        while (hit == false) //DDA 알고리즘
        {
            if (side_dist[X] < side_dist[Y])
            {
                side_dist[X] += delta_dist[X];
                map.x += step.x;
                side = 0;
            }
            else
            {
                side_dist[Y] += delta_dist[Y];
                map.y += step.y;
                side = 1;
            }
			//광선이 벽과 만났는지 확인
            if (info->map->scene[map.y][map.x] == '1')
                hit = true;
        }
		-->calc.c : hit_loop() */
		/*
        if (side == 0)  // y축에 평행하게 벽에 충돌
            perpWallDist = (map.x - info->calc->pos->x + (1 - step.x) / 2) / info->calc->ray->x;
        else            // x축에 평행하게 벽에 충돌
            perpWallDist = (map.y - info->calc->pos->y + (1 - step.y) / 2) / info->calc->ray->y;
        lineHeight = (int)(1080 / perpWallDist); //화면에 그려야하는 선의 길이
		--> calc.:calc_ves() */
        ///////////////////////////////////////////////////
        /*
        drawStart = -lineHeight / 2 + 1080 / 2;
        if (drawStart < 0)
            drawStart = 0;
        drawEnd = lineHeight / 2 + 1080 / 2;
        if (drawEnd >= 1080)
            drawEnd = 1080 - 1;
        if (side == 0)
            wallX = info->calc->pos->y + perpWallDist * info->calc->ray->y;
        else
            wallX = info->calc->pos->x + perpWallDist * info->calc->ray->x;
        wallX -= floor((wallX));

        tex.x = (int) (wallX * (double)(425));
        if (side == 0 && info->calc->ray->x > 0)
            tex.x = 425 - tex.x - 1;
        if (side == 1 && info->calc->ray->y < 0)
            tex.x = 425 - tex.x - 1;

        ratio = 1.0 * 425 / lineHeight;
        texPos = (drawStart - 1080 / 2 + lineHeight / 2) * ratio;

        화면의 색깔을 불러오는 부분
        screen.y = 0;
        while (screen.y < drawStart)
        {
            color = create_color(info->texture->ceiling);
            *(info->screen->addr + screen.y * 1920 + screen.x) = color;
            screen.y++;
        }
        while (screen.y < drawEnd)
        {
            tex.y = (int) texPos % 425;
            texPos += ratio;
            if (side == 0)
            {
                if (info->calc->ray->x >= 0)
                    color = info->texture->west->addr[info->texture->west->height * tex.y + tex.x];
                else
                    color = info->texture->east->addr[info->texture->east->height * tex.y + tex.x];
            }
            else
            {
                if (info->calc->ray->y >= 0)
                    color = info->texture->north->addr[info->texture->north->height * tex.y + tex.x];
                else
                    color = info->texture->south->addr[info->texture->south->height * tex.y + tex.x];
            }
            *(info->screen->addr + screen.y * 1920 + screen.x) = color;
            screen.y++;
        }
        while (screen.y < 1080)
        {
            color = create_color(info->texture->floor);
            *(info->screen->addr + screen.y * 1920 + screen.x) = color;
            screen.y++;
        }
        mlx_put_image_to_window(info->mlx, info->win, info->screen->ptr, 0, 0);
        */
        screen.x++;
    }
    mlx_hook(info->win, 17, 0, &dev_close, 0);
	mlx_hook(info->win, 2, 0, &key_press, 0);
    mlx_loop(info->mlx);
}
