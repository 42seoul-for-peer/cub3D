/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_raycasting_tutorial.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeunkim <hyeunkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 14:56:14 by seungjun          #+#    #+#             */
/*   Updated: 2024/06/14 15:48:14 by hyeunkim         ###   ########.fr       */
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

void print_color(t_info *info, int width, int h_start, int h_end, int color)
{
    while (h_start < h_end)
    {
        // if (dir == 'E')
        //     mlx_put_image_to_window(info->mlx, info->win, info->texture->east, 96 * po.x, 96 * po.y);
        mlx_pixel_put(info->mlx, info->win, width, h_start, color);
        h_start++;
    }
}

#include <stdio.h>

void    tutorial(t_info *info)
{
    t_vector    pos;        // 플레이어의 시작 위치
    t_vector    dir;        // 초기 방향 벡터(불변)
    dir = init_dir_vector(info->map->player_pos[2]);
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

    info->img->img = mlx_new_image(info->mlx, 1920, 1080); //화면에 씌울 이미지 생성 (image buffer)
    info->img->addr = (int *) mlx_get_data_addr(info->img->img, &(info->img->bpp), \
									&(info->img->line), &(info->img->endian));
                                    
    pos.x = info->map->player_pos[0];
    pos.y = info->map->player_pos[1];

    plane = init_plane_vector(dir);
    idx_x = 0;
    while (idx_x < 1920)
    {
        hit = false;

        cameraX = 2 * idx_x / (double)1920 - 1; //카메라 평면에서의 x좌표
        rayDir.x = dir.x + plane.x * cameraX;
        rayDir.y = dir.y + plane.y * cameraX;

		//플레이어가 위치한 격자의 좌표
        mapX = pos.x;
        mapY = pos.y;
        deltaDistX = fabs(1 / rayDir.x); //x가 1 증가할 때 광선의 이동 거리
        deltaDistY = fabs(1 / rayDir.y); //y가 1 증가할 때 광선의 이동 거리
        if (rayDir.x < 0) //왼쪽으로 이동하다 처음 만나는 x면까지의 거리
        {
            stepX = -1;
            sideDistX = (pos.x - mapX) * deltaDistX;
        }
        else // sideDistX : raydir.x> 0인 경우 광선의 시작부터 오른쪽으로 이동하다 처음 만나는 x면까지의 거리
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
        while (hit == false) //DDA 알고리즘
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
			//광선이 벽과 만났는지 확인
            if (info->map->scene[mapY][mapX] == '1' || info->map->scene[mapY][mapX] == '2')
                hit = true;
        }
        if (side == 0)  // y축에 평행하게 벽에 충돌
            perpWallDist = (mapX - pos.x + (1 - stepX) / 2) / rayDir.x;
        else            // x축에 평행하게 벽에 충돌
            perpWallDist = (mapY - pos.y + (1 - stepY) / 2) / rayDir.y;
        lineHeight = (int)(1080 / perpWallDist); //화면에 그려야하는 선의 길이
        drawStart = -lineHeight / 2 + 1080 / 2;
        if (drawStart < 0)
            drawStart = 0;
        drawEnd = lineHeight / 2 + 1080 / 2;
        if (drawEnd >= 1080)
            drawEnd = 1080 - 1;

        double wallX; //벽과 부딪힌 자리의 X좌표
        if (side == 0)
            wallX = pos.y + perpWallDist * rayDir.y;
        else
            wallX = pos.x + perpWallDist * rayDir.x;
        wallX -= floor((wallX));

        int texX = (int) (wallX * (double)(425));
        if (side == 0 && rayDir.x > 0)
            texX = 425 - texX - 1;
        if (side == 1 && rayDir.y < 0)
            texX = 425 - texX - 1;

        double step = 1.0 * 425 / lineHeight;
        double texPos = (drawStart - 1080 / 2 + lineHeight / 2) * step;

        ft_printf("drawstart & end: %d ~ %d\n", drawStart, drawEnd);
        int prev_color = 0;
        for (int y = drawStart; y < drawEnd; y++) // y: 화면상의 픽셀 좌표
        {
            int texY = (int)texPos % 425;
            texPos += step;
            if (side == 0)
            {
                if (rayDir.x >= 0)
                    color = info->texture->west->addr[info->texture->west->height * texY + texX];
                else
                    color = info->texture->east->addr[info->texture->east->height * texY + texX];
            }
            else
            {
                if (rayDir.y >= 0)
                    color = info->texture->north->addr[info->texture->north->height * texY + texX];
                else
                    color = info->texture->south->addr[info->texture->south->height * texY + texX];
            }
            if (prev_color == 0)
            {
                ft_printf("now focusing on texPos(%d, %d) for (%d, %d) ", texX, texY, idx_x, y);
                ft_printf(" %X \n",color);
                prev_color = color;
            }
            if (prev_color != 0 && color != prev_color)
            {
                ft_printf("now focusing on (%d, %d) for (%d, %d) ", texX, texY, idx_x, y);
                ft_printf(" %X \n",color);
                prev_color = color;
            }
            *(info->img->addr + y * 1920 + idx_x) = color;
        }
        ft_printf("\n");
        mlx_put_image_to_window(info->mlx, info->win, info->img->img, 0, 0);
        idx_x++;
    }
}
