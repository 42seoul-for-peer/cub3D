/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeunkim <hyeunkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 14:12:21 by hyeunkim          #+#    #+#             */
/*   Updated: 2024/06/23 14:43:18 by hyeunkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>

int	get_color_from_colorset(int *colorset)
{
	return (colorset[0] << 16 | colorset[1] << 8 | colorset[2]);
}

void	set_screen_color(t_info *info, t_draw draw)
{
	t_coor	tex_pos;
	int		height;
	int		color;

	height = 0;
	tex_pos = draw.texture;
	while (height < WIN_HEIGHT)
	{
		if (height < draw.start_height)
			color = get_color_from_colorset(info->texture->ceiling);
		else if (height < draw.end_height)
		{
			tex_pos.y = (int) draw.tex_height_unit % draw.img->height;
			draw.tex_height_unit += draw.ratio;
			color = draw.img->addr[draw.img->height * tex_pos.y + tex_pos.x];
		}
		else
			color = get_color_from_colorset(info->texture->floor);
		*(info->screen->addr + height * WIN_WIDTH + draw.screen_width) = color;
		height++;
	}
}

void	set_image_data(t_draw *draw, t_data *calc, t_tex *texture)
{
	if (draw->side == X && calc->ray->x >= 0)
		draw->img = texture->west;
	else if (draw->side == X && calc->ray->x < 0)
		draw->img = texture->east;
	else if (draw->side == Y && calc->ray->y >= 0)
		draw->img = texture->north;
	else if (draw->side == Y && calc->ray->y < 0)
		draw->img = texture->south;
	draw->texture.x = (int)(draw->wall_x * (double) draw->img->width);
	if (draw->side == X && calc->ray->x < 0)
		draw->texture.x = draw->img->width - draw->texture.x - 1;
	if (draw->side == Y && calc->ray->y > 0)
		draw->texture.x = draw->img->width - draw->texture.x - 1;
	draw->ratio = 1.0 * draw->img->height / calc->line_height;
	draw->tex_height_unit = \
	(draw->start_height - WIN_HEIGHT / 2 + calc->line_height / 2) * draw->ratio;
}

t_draw	get_draw_data(t_data *calc, int screen_width)
{
	t_draw	draw;

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
	return (draw);
}

void	draw(t_info *info, int screen_width)
{
	t_draw	draw;

	draw = get_draw_data(info->calc, screen_width);
	set_image_data(&draw, info->calc, info->texture);
	set_screen_color(info, draw);
}
