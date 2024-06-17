/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_print_map.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeunkim <hyeunkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 14:15:44 by seungjun          #+#    #+#             */
/*   Updated: 2024/06/13 18:07:37 by hyeunkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void print_color(t_info *info, int width, int height, int color)
{
    int idx_h;
    int idx_w;

    idx_h = 0;
    while (idx_h < 60)
    {
        idx_w = 0;
        while (idx_w < 60)
        {
            mlx_pixel_put(info->mlx, info->win, width * 60 + idx_w, height * 60 + idx_h, color);
            idx_w++;
        }
        idx_h++;
    }
}

void    print_map(t_map *map, t_info *info)
{
    int width;
    int height;

    width = 0;
    height = 0;

    while (height < map->height)
    {
        width = 0;
        while (width < map->width)
        {
            if (map->scene[height][width] == '0')
                print_color(info, width, height, 0x00FFFFFF);
            else if (map->scene[height][width] == '1')
                print_color(info, width, height, 0x005245D3);
            else if (map->scene[height][width] == 'P')
                print_color(info, width, height, 0x00F53530);
            width++;
        }
        height++;
    }
}