/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_check_map.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeunkim <hyeunkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 17:51:22 by hyeunkim          #+#    #+#             */
/*   Updated: 2024/06/09 16:51:10 by hyeunkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
1. 맵은 0, 1, (N, S, W, E 중 1개), ' ' 로만 구성되어야 함
2. 맵이 둘러싸여져 있어야 함 -> 0이 삐져나와 있으면 안된다
   -> 0에 인접하는 것이 ' '이거나 마지막 index면 안된다
*/

bool    get_player_pos(t_map *map, int idx_h, int idx_w, char elem)
{
    if (map->player_pos != 0)
        return (false);
    map->player_pos = ft_calloc(3, sizeof(int));
    if (!map->player_pos)
        print_error(sys_call);
    map->player_pos[0] = idx_w;
    map->player_pos[1] = idx_h;
    map->player_pos[2] = elem;
    return (true);
}

bool    check_map_elements(t_map *map)
{
    char    elem;
    int     idx_h;
    int     idx_w;

    idx_h = 0;
    while (idx_h < map->height)
    {
        idx_w = 0;
        while (idx_w < map->width && map->scene[idx_h][idx_w])
        {
            elem = map->scene[idx_h][idx_w];
            if (elem == 'N' || elem == 'S' || elem == 'E' || elem == 'W')
            {
                if (get_player_pos(map, idx_h, idx_w, elem) == false)
                    return (false);
            }
            else if (elem != '0' && elem != '1' && elem != ' ')
                return (false);
            idx_w++;
        }
        idx_h++;
    }
    return (true);
}

bool    check_map_surrounded(t_map *map)
{
    (void) map;
    return (true);
}

bool    check_map_format(t_map *map)
{
    (void) map;

    if (check_map_elements(map) == false)
        return (false);
    else if (check_map_surrounded(map) == false)
        return (false);
    return (true);
}