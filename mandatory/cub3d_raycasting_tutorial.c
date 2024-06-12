/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_raycasting_tutorial.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungjun <seungjun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 14:56:14 by seungjun          #+#    #+#             */
/*   Updated: 2024/06/11 14:56:31 by seungjun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

typedef struct s_vector
{
    double x;
    double y;
}   t_vector;

t_vector    init_dir_vector(char flag)
{
    t_vector    dir;

    if (flag == 'N')
    {
        dir.x = 0;
        dir.y = -1;
    }
    else if (flag == 'S')
    {
        dir.x = 0;
        dir.y = 1;
    }
    else if (flag == 'W')
    {
        dir.x = -1;
        dir.y = 0;
    }
    else
    {
        dir.x = 1;
        dir.y = 0;
    }
    return (dir);
}

t_vector    init_plane_vector(t_vector dir)
{
    t_vector    plane;

    if (dir.x == 0)
    {
        plane.x = 1;
        plane.y = 0;
    }
    else
    {
        plane.x = 0;
        plane.y = 1;
    }
    return (plane);
}

double  ft_abs(double num)
{
    if (num < 0)
        return (num * -1);
    else
        return (num);
}

void print_color(t_mlx mlx, int width, int h_start, int h_end, int color)
{
    while (h_start < h_end)
    {
        mlx_pixel_put(mlx.mlx, mlx.win, width, h_start, color);
        h_start++;
    }
}

#include <stdio.h>

void    tutorial(t_map *map, t_mlx mlx)
{
    t_vector    pos;        // 플레이어의 위치
    t_vector    dir;        // 방향 벡터(불변)
    dir = init_dir_vector(map->player_pos[2]);
    t_vector    plane;      // 플레이어가 바라보는 카메라 평면(출력 화면, 불변)
    t_vector    rayDir;     // 광선의 방향 벡터

    double  cameraX;        // x축 0부터 1920까지 광선을 쏠 때, 그 광선의 카메라 평면 x좌표

    double  sideDistX;      // [시작점] -> [첫번째 x면] 까지의 광선 이동거리
    double  sideDistY;      // [시작점] -> [첫번째 y면] 까지의 광선 이동거리
    double  deltaDistX;     // [x면] -> [다음 x면] 까지의 광선 이동거리
    double  deltaDistY;     // [y면] -> [다음 y면] 까지의 광선 이동거리
    double  perpWallDist;   // 광선의 총 이동거리

    int     idx_x;          // 출력 화면의 x좌표
    int     mapX;           // 현재 가리키는 맵의 x좌표
    int     mapY;           // 현재 가리키는 맵의 y좌표
    int     stepX;          // 광선이 나아가며 변동되는 x축 int 변화량
    int     stepY;          // 광선이 나아가며 변동되는 x축 int 변화량
    int     side;           // x축 평행 벽에 닿았는지, y축 평행 벽에 닿았는지 판단 인덱스

    bool     hit;           // 벽에 닿았는지 여부 파악

    int     lineHeight;     // 화면에 그리기 위한 높이
    int     drawStart;      // 화면에 그려기 위한 높이의 start값
    int     drawEnd;        // 화면에 그리기 위한 높이의 end값      (둘이 합하면 화면 출력 높이(height))
    int     color;          // Color값

    pos.x = map->player_pos[0];
    pos.y = map->player_pos[1];
    
    plane = init_plane_vector(dir);
    idx_x = 0;
    while (idx_x < 1920)
    {
        hit = false;

        cameraX = 2 * idx_x / (double)1920 - 1;
        rayDir.x = dir.x + plane.x * cameraX;
        rayDir.y = dir.y + plane.y * cameraX;

        mapX = pos.x;
        mapY = pos.y;
        deltaDistX = ft_abs(1 / rayDir.x);
        deltaDistY = ft_abs(1 / rayDir.y);
        if (rayDir.x < 0)
        {
            stepX = -1;
            sideDistX = (pos.x - mapX) * deltaDistX;
        }
        else
        {
            stepX = 1;
            sideDistX = (mapX + 1.0 - pos.x) * deltaDistX;
        }
        if (rayDir.y < 0)
        {
            stepY = -1;
            sideDistY = (pos.y - mapY) * deltaDistY;
        }
        else
        {
            stepY = 1;
            sideDistY = (mapY + 1.0 - pos.y) * deltaDistY;
        }
        while (hit == false)
        {
            if (sideDistX < sideDistY)
            {
                sideDistX += deltaDistX;
                mapX += stepX;
                side = 0;
            }
            else
            {
                sideDistY += deltaDistY;
                mapY += stepY;
                side = 1;
            }
            if (map->scene[mapY][mapX] == '1' || map->scene[mapY][mapX] == '2')
                hit = true;
        }
        ft_printf("mapX, mapY : %d, %d\n", mapX, mapY);
        if (side == 0)
            perpWallDist = (mapX - pos.x + (1 - stepX) / 2) / rayDir.x;
        else
            perpWallDist = (mapY - pos.y + (1 - stepY) / 2) / rayDir.y;
    
        lineHeight = (int)(1080 / perpWallDist);
        drawStart = -lineHeight / 2 + 1080 / 2;
        if (drawStart < 0)
            drawStart = 0;
        drawEnd = lineHeight / 2 + 1080 / 2;
        if (drawEnd >= 1080)
            drawEnd = 1080 - 1;

        if (map->scene[mapY][mapX] == '0')
            color = 0x00FFFFFF;
        else if (map->scene[mapY][mapX] == '1')
            color = 0x005245D3;
        else if (map->scene[mapY][mapX] == '2')
            color = 0x00F53530;
        else if (map->scene[mapY][mapX] == 'P')
            color = 0x00F53530;
        print_color(mlx, idx_x, drawStart, drawEnd, color);
        idx_x++;
    }
}