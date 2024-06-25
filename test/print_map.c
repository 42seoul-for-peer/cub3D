/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeunkim <hyeunkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 14:15:44 by seungjun          #+#    #+#             */
/*   Updated: 2024/06/24 19:02:38 by hyeunkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void print_color(t_info *info, int w, int h, int color)
{
    int idx_h;
    int idx_w;

    idx_h = 0;
    while (idx_h < 60)
    {
        idx_w = 0;
        while (idx_w < 60)
        {
            mlx_pixel_put(info->mlx, info->win, w * 60 + idx_w, h * 60 + idx_h, color);
            idx_w++;
        }
        idx_h++;
    }
}

void    print_map(t_map *map, t_info *info)
{
    int w;
    int h;

    w = 0;
    h = 0;

    while (h < map->h)
    {
        w = 0;
        while (w < map->w)
        {
            if (map->scene[h][w] == '0')
                print_color(info, w, h, 0x00FFFFFF);
            else if (map->scene[h][w] == '1')
                print_color(info, w, h, 0x005245D3);
            else if (map->scene[h][w] == 'P')
                print_color(info, w, h, 0x00F53530);
            w++;
        }
        h++;
    }
}