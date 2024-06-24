/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_format.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeunkim <hyeunkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 17:51:22 by hyeunkim          #+#    #+#             */
/*   Updated: 2024/06/24 22:08:13 by hyeunkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
1. 맵은 0, 1, (N, S, W, E 중 1개), 0 로만 구성되어야 함
2. 맵이 둘러싸여져 있어야 함 -> 0이 삐져나와 있으면 안된다
   -> 0에 인접하는 것이 0이거나 마지막 index면 안된다
*/

bool    get_player_pos(t_map *map, int idx_h, int idx_w, char elem)
{
    if (map->player_dir != 0)
        return (false);
    map->pos.x = idx_w;
    map->pos.y = idx_h;
    map->player_dir = elem;
    map->scene[idx_h][idx_w] = 'P';
    return (true);
}

bool    check_map_elements(t_map *map)
{
    char    elem;
    int     idx_h;
    int     idx_w;

    idx_h = 0;
    while (idx_h < map->h)
    {
        idx_w = 0;
        while (idx_w < map->w && map->scene[idx_h][idx_w])
        {
            elem = map->scene[idx_h][idx_w];
            if (elem == 'N' || elem == 'S' || elem == 'E' || elem == 'W')
            {
                if (get_player_pos(map, idx_h, idx_w, elem) == false)
                    return (false);
            }
            else if (elem != '0' && elem != '1' && elem != 0 && elem != ' ')
                return (false);
            idx_w++;
        }
        idx_h++;
    }
    if (map->player_dir == 0)
        return (false);
    return (true);
}

char    **get_copied_scene(t_map *map)
{
    char    **scene_copy;
    int     idx;

    idx = 0;
    scene_copy = ft_calloc(map->h + 1, sizeof(char *));
    if (!scene_copy)
        exit_with_error(sys_call);
    while (idx < map->h)
    {
        scene_copy[idx] = ft_calloc(map->w + 1, sizeof(char *));
        if (!scene_copy[idx])
            exit_with_error(sys_call);
        ft_strlcpy(scene_copy[idx], map->scene[idx], map->w + 1);
        idx++;
    }
    scene_copy[map->h] = 0;
    return (scene_copy);
}

bool    check_void_nearby(t_map *map, int idx_h, int idx_w)
{
    char    elem_up;
    char    elem_down;
    char    elem_left;
    char    elem_right;

    if (idx_h == 0 || idx_h == map->h - 1)
        return (false);
    if (idx_w == 0 || idx_w == map->w - 1)
        return (false);
    elem_up = map->scene[idx_h - 1][idx_w];
    elem_down = map->scene[idx_h + 1][idx_w];
    elem_left = map->scene[idx_h][idx_w + 1];
    elem_right = map->scene[idx_h][idx_w - 1];
    if (elem_up == 0 || elem_down == 0 || elem_right == 0 || elem_left == 0)
        return (false);
    if (elem_up == ' ' || elem_down == ' ' || elem_right == ' ' || elem_left == ' ')
        return (false);
    return (true);
}

bool    check_map_surrounded(t_map *map)
{
    char    **scene_backup;
    char    elem;
    int     idx_h;
    int     idx_w;

    idx_h = 0;
    scene_backup = get_copied_scene(map);
    while (idx_h < map->h)
    {
        idx_w = 0;
        while (idx_w < map->w)
        {
            elem = map->scene[idx_h][idx_w];
            if (elem == '0' || elem == 'P')
            {
                if (check_void_nearby(map, idx_h, idx_w) == false)
                    return (false);
            }
            idx_w++;
        }
        idx_h++;
    }
    free(map->scene);
    map->scene = scene_backup;
    return (true);
}

bool    check_map_format(t_map *map)
{
    if (check_map_elements(map) == false)
        return (false);
    else if (check_map_surrounded(map) == false)
        return (false);
    return (true);
}
