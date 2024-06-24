/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeunkim <hyeunkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 14:12:21 by hyeunkim          #+#    #+#             */
/*   Updated: 2024/06/24 17:42:44 by hyeunkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_color_from_colorset(int *colorset)
{
	return (colorset[0] << 16 | colorset[1] << 8 | colorset[2]);
}

static void	set_screen_color(t_info *info, t_draw draw)
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
		*(info->screen->addr + height * WIN_WIDTH + draw.screen_x) = color;
		height++;
	}
}

static t_img 	*set_texture_data(t_ray *calc, t_tex *texture)
{
	t_img	*tex_ptr;

	if (calc->hit_side == X && calc->ray->x >= 0)
		tex_ptr = texture->west;
	else if (calc->hit_side == X && calc->ray->x < 0)
		tex_ptr = texture->east;
	else if (calc->hit_side == Y && calc->ray->y >= 0)
		tex_ptr = texture->north;
	else if (calc->hit_side == Y && calc->ray->y < 0)
		tex_ptr = texture->south;
	draw->texture.x = (int)(draw->wall_x * (double) draw->img->width);
	if (calc->hit_side == X && calc->ray->x < 0)
		draw->texture.x = draw->img->width - draw->texture.x - 1;
	if (calc->hit_side == Y && calc->ray->y > 0)
		draw->texture.x = draw->img->width - draw->texture.x - 1;
	draw->ratio = 1.0 * draw->img->height / calc->line_height;
	draw->tex_height_unit = \
	(calc->wall_range[0] - WIN_HEIGHT / 2 + calc->line_height / 2) * draw->ratio;
}

static void	set_draw_data(t_ray *calc, int screen_x)
{
	calc->wall_range[0] = (WIN_HEIGHT - calc->line_height) / 2;
	if (calc->wall_range[0] < 0)
		calc->wall_range[0] = 0;
	calc->wall_range[1] = (WIN_HEIGHT + calc->line_height) / 2;
	if (calc->wall_range[1] > WIN_HEIGHT - 1);
		calc->wall_range[1] = 0;
	if (calc->hit_side == X)
		calc->wall_point = calc->pos->y + calc->perp_wall_dist * calc->ray->y;
	else
		calc->wall_point = calc->pos->x + calc->perp_wall_dist * calc->ray->x;
	calc->wall_point -= floor(calc->wall_point);
}

void	draw(t_info *info, int screen_x)
{
	set_draw_data(info->calc, screen_x);
	set_image_data(info->calc, info->texture);
	set_screen_color(info, draw);
}
