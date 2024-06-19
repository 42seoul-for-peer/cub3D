/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_tutorial.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeunkim <hyeunkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 14:56:14 by seungjun          #+#    #+#             */
/*   Updated: 2024/06/19 18:06:32 by hyeunkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>

# define MOVE_SPEED 1
# define KEY_ESC 53
# define KEY_W 13
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_LEFT 123
# define KEY_RIGHT 124

typedef struct s_tmp
{
    t_info  *info;
    t_vec   *pos;
    t_vec   *dir;
    t_vec   *plane;
}   t_tmp;

int dev_close(int key, void *temp) //mlx key hook (ESC)
{
	temp = 0;
	if (key == 53)
		exit(0);
	return (0);
}

int	key_press(int key, t_tmp *tmp)
{
    char    **scene;
    t_vec   *pos;
    t_vec   *dir;
    t_vec   *plane;

    scene = tmp->info->map->scene;
    pos = tmp->pos;
    dir = tmp->dir;
    plane = tmp->plane;
	if (key == KEY_ESC)
		dev_close(53, 0);
    if (key == KEY_W)
    {
		printf(">tartget: (%f, %f)\n", pos->x + dir->x * MOVE_SPEED, pos->y);
        if(scene[(int) pos->y][(int) (pos->x + dir->x * MOVE_SPEED)] != '1')
            pos->x += dir->x * MOVE_SPEED;
		printf(">>target: (%f, %f)\n", pos->x, pos->y + dir->y * MOVE_SPEED);
        if(scene[(int) (pos->y + dir->y * MOVE_SPEED)][(int) pos->x] != '1')
            pos->y += dir->y * MOVE_SPEED;
		printf(">>>position: (%f, %f)\n", pos->x, pos->y);
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
	return (0);
}

t_vec    *init_dir_vector(char flag)
{
    t_vec    *dir;

    if (flag == 'N')
    {
        dir->x = 0;
        dir->y = -1;
    }
    else if (flag == 'S')
    {
        dir->x = 0;
        dir->y = 1;
    }
    else if (flag == 'W')
    {
        dir->x = -1;
        dir->y = 0;
    }
    else
    {
        dir->x = 1;
        dir->y = 0;
    }
    return (dir);
}

t_vec    *init_plane_vector(t_vec *dir)
{
    t_vec    *plane;

    plane = ft_calloc(1, sizeof(t_vec));
    if (dir->x == 0)
    {
        plane->x = 1;
        plane->y = 0;
    }
    else
    {
        plane->x = 0;
        plane->y = 1;
    }
    return (plane);
}

int create_color(int *colorset)
{
    return (colorset[0] << 16 | colorset[1] << 8 | colorset[2]);
}

void    tutorial(t_info *info)
{
    t_vec    *pos;        // 플레이어의 시작 위치
    t_vec    *dir;        // 초기 방향 벡터(불변)
    t_vec    *plane;      // 플레이어가 바라보는 카메라 평면(출력 화면, 불변)
    t_vec    raydir;     // 광선의 방향 벡터

    double  cameraX;        // x축 0부터 1920까지 광선을 쏠 때, 그 광선의 카메라 평면 x좌표
    double  side_dist[2];   // [시작점] -> [첫번째 x또는 y면] 까지의 광선 이동거리
    double  delta_dist[2];	// [x면] -> [다음 x면] 또는 [y면] -> [다음 y면] 까지의 광선 이동거리
    double  perpWallDist;   // 광선의 총 이동거리
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

    t_tmp   *tmp;
    tmp = ft_calloc(1, sizeof(t_tmp));
	if (!tmp)
		print_error(sys_call, __func__, __LINE__);
    pos = ft_calloc(1, sizeof(t_vec));
    dir = ft_calloc(1, sizeof(t_vec));
    plane = init_plane_vector(dir);
    tmp->info = info;
    tmp->pos = pos;
    tmp->dir = dir;
    tmp->plane = plane;

    screen.x = 0;
    dir = init_dir_vector(info->map->player_dir);
    pos->x = info->map->pos.x + 0.5;
    pos->y = info->map->pos.y + 0.5;
	printf("position(%f, %f)\n", pos->x, pos->y);

    while (screen.x < 1920)
    {
        hit = false;

        cameraX = 2 * screen.x / (double)1920 - 1; //카메라 평면에서의 x좌표
        raydir.x = dir->x + plane->x * cameraX;
        raydir.y = dir->y + plane->y * cameraX;

		//플레이어가 위치한 격자의 좌표
        map.x = pos->x;
        map.y = pos->y;
        delta_dist[X] = fabs(1 / raydir.x); //x가 1 증가할 때 광선의 이동 거리
        delta_dist[Y] = fabs(1 / raydir.y); //y가 1 증가할 때 광선의 이동 거리
        if (raydir.x < 0) //왼쪽으로 이동하다 처음 만나는 x면까지의 거리
        {
            step.x = -1;
            side_dist[X] = (pos->x - map.x) * delta_dist[X];
        }
        else // side_dist[X] : raydir.x> 0인 경우 광선의 시작부터 오른쪽으로 이동하다 처음 만나는 x면까지의 거리
        {
            step.x = 1;
            side_dist[X] = (map.x + 1.0 - pos->x) * delta_dist[X];
        }
        if (raydir.y < 0)
        {
            step.y = -1;
            side_dist[Y] = (pos->y - map.y) * delta_dist[Y];
        }
        else
        {
            step.y = 1;
            side_dist[Y] = (map.y + 1.0 - pos->y) * delta_dist[Y];
        }
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
        if (side == 0)  // y축에 평행하게 벽에 충돌
            perpWallDist = (map.x - pos->x + (1 - step.x) / 2) / raydir.x;
        else            // x축에 평행하게 벽에 충돌
            perpWallDist = (map.y - pos->y + (1 - step.y) / 2) / raydir.y;
        lineHeight = (int)(1080 / perpWallDist); //화면에 그려야하는 선의 길이
        drawStart = -lineHeight / 2 + 1080 / 2;
        if (drawStart < 0)
            drawStart = 0;
        drawEnd = lineHeight / 2 + 1080 / 2;
        if (drawEnd >= 1080)
            drawEnd = 1080 - 1;

        if (side == 0)
            wallX = pos->y + perpWallDist * raydir.y;
        else
            wallX = pos->x + perpWallDist * raydir.x;
        wallX -= floor((wallX));

        tex.x = (int) (wallX * (double)(425));
        if (side == 0 && raydir.x > 0)
            tex.x = 425 - tex.x - 1;
        if (side == 1 && raydir.y < 0)
            tex.x = 425 - tex.x - 1;

        ratio = 1.0 * 425 / lineHeight;
        texPos = (drawStart - 1080 / 2 + lineHeight / 2) * ratio;

        /* 화면의 색깔을 불러오는 부분*/
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
                if (raydir.x >= 0)
                    color = info->texture->west->addr[info->texture->west->height * tex.y + tex.x];
                else
                    color = info->texture->east->addr[info->texture->east->height * tex.y + tex.x];
            }
            else
            {
                if (raydir.y >= 0)
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
        screen.x++;
    }
    mlx_hook(info->win, 17, 0, &dev_close, 0);
	mlx_hook(info->win, 2, 0, &key_press, tmp);
    mlx_loop(info->mlx);
}
