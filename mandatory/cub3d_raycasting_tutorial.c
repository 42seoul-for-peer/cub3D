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
        dir.y = 1;
    }
    else if (flag == 'S')
    {
        dir.x = 0;
        dir.y = -1;
    }
    else if (flag == 'W')
    {
        dir.x = -1;
        dir.y = 0;
    }
    else if (flag == 'E')
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
    else if (dir.y == 0)
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

void    tutorial(t_map *map, t_mlx mlx)
{
    t_vector    pos;
    t_vector    dir;
    t_vector    plane;
    t_vector    rayDir;

    double  cameraX;
    double  sideDistX;
    double  sideDistY;
    double  deltaDistX;
    double  deltaDistY;

    int     idx_x;
    int     mapX;
    int     mapY;

    pos.x = map->player_pos[0];
    pos.y = map->player_pos[1];
    dir = init_dir_vector(map->player_pos[2]);
    plane = init_plane_vector(dir);
    idx_x = 0;
    while (idx_x < 1920)
    {
        cameraX = 2 * idx_x / 1920 - 1;
        rayDir.x = dir.x + plane.x * cameraX;
        rayDir.y = dir.y + plane.y * cameraX;

        mapX = pos.x;
        mapY = pos.y;
        deltaDistX = ft_abs(1 / rayDir.x);
        deltaDistY = ft_abs(1 / rayDir.y);
        idx_x++;
    }
}