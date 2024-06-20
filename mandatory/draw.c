/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeunkim <hyeunkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 14:12:21 by hyeunkim          #+#    #+#             */
/*   Updated: 2024/06/20 16:23:17 by hyeunkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int get_color_from_colorset(int *colorset)
{
    return (colorset[0] << 16 | colorset[1] << 8 | colorset[2]);
}

int get_color_from_texture(t_info *info, t_draw draw)
{
    t_img   *img;

	img = NULL;
    if (draw.side == X && info->calc->ray->x >= 0)
        img = info->texture->west;
    else if (draw.side == X && info->calc->ray->x < 0)
        img = info->texture->east;
    else if (draw.side == Y && info->calc->ray->y >= 0)
        img = info->texture->north;
    else if (draw.side == Y && info->calc->ray->y < 0)
        img = info->texture->south;
    return (img->addr[img->height * draw.texture.y + draw.texture.x]);
}

void    set_screen_color(t_info *info, t_draw draw)
{
    int screen_height;
    int color;

    screen_height = 0;
    while (screen_height < WIN_HEIGHT)
    {
        if (screen_height < draw.start_height)
            color = get_color_from_colorset(info->texture->ceiling);
        else if (screen_height < draw.end_height)
        {
            draw.texture.y = (int) draw.tex_height_unit % 425;
            draw.tex_height_unit += draw.ratio;
            color = get_color_from_texture(info, draw);
        }
        else
            color = get_color_from_colorset(info->texture->floor);
        *(info->screen->addr + screen_height * WIN_WIDTH + draw.screen_width) = color;
        screen_height++;
    }
}

t_draw  get_draw_data(t_data *calc, int screen_width)
{
    t_draw  draw;

    draw.screen_width = screen_width;
    draw.side = calc->side;
    draw.start_height = -calc->line_height / 2 + WIN_HEIGHT / 2;
    if (draw.start_height < 0)
        draw.start_height = 0;
    draw.end_height = calc->line_height / 2 + WIN_HEIGHT / 2;
    if (draw.end_height >= WIN_HEIGHT)
        draw.end_height = WIN_HEIGHT - 1;
    if (draw.side == X)
        draw.wall_x = calc->pos->y + calc->perp_wall_dist * calc->ray->y;
    else
        draw.wall_x = calc->pos->x + calc->perp_wall_dist * calc->ray->x;
    draw.wall_x -= floor((draw.wall_x));
    draw.texture.x = (int) (draw.wall_x * (double) 425);
    if (draw.side == X && calc->ray->x > 0)
        draw.texture.x = 425 - draw.texture.x - 1;
    if (draw.side == Y && calc->ray->y < 0)
        draw.texture.x = 425 - draw.texture.x - 1;
    draw.ratio = 1.0 * 425 / calc->line_height;
    draw.tex_height_unit = (draw.start_height - WIN_HEIGHT / 2 + calc->line_height / 2) * draw.ratio;
    return (draw);
}

void    draw(t_info *info, int screen_width)
{
    t_draw  draw;

    draw = get_draw_data(info->calc, screen_width);
    set_screen_color(info, draw);
    mlx_put_image_to_window(info->mlx, info->win, info->screen->ptr, 0, 0);
}