/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeunkim <hyeunkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 14:12:21 by hyeunkim          #+#    #+#             */
/*   Updated: 2024/06/24 21:34:55 by hyeunkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>
static int	get_color(int *colorset)
{
	return (colorset[0] << 16 | colorset[1] << 8 | colorset[2]);
}

int test(int color, t_ray *ray)
{
	int r;
	int g;
	int b;
	

	r = (color >> 16) & 0xFF;
	g = (color >> 8) & 0xFF;
	b = color & 0xFF;
	if (ray->perp_wall_dist > 12)
	{
		r = 255;
		g = 255;
		b = 255;
	}
	else
	{
		r = r + (int)((255 - r) * (ray->perp_wall_dist / 12.0));
		g = g + (int)((255 - g) * (ray->perp_wall_dist / 12.0));
		b = b + (int)((255 - b) * (ray->perp_wall_dist / 12.0));
	}
	
	if ((double)ray->tex_pos->x / (double)ray->tex_ptr->w < 0.01 || (double)ray->tex_pos->x / (double)ray->tex_ptr->w > 0.99)
	{
		r = 0;
		g = 0;
		b = 0;
	}
	else if ((double)ray->tex_pos->y / (double)ray->tex_ptr->h < 0.01 || (double)ray->tex_pos->y / (double)ray->tex_ptr->h > 0.99)
	{
		r = 0;
		g = 0;
		b = 0;
	}
	return (r << 16 | g << 8 | b);
}

static void	set_scr_color(t_ray *ray, t_tex *tex, t_img *scr, int scr_x)
{
	int		scr_y;
	int		color;
	int		*tex_addr;
	double	tex_h_unit;
	//double	percent;

	tex_h_unit = \
		(ray->wall_rng[0] + (ray->line_len - WIN_H) / 2) * ray->tex_rate;
	scr_y = 0;
	while (scr_y < WIN_H)
	{
		if (scr_y < ray->wall_rng[0])
			color = get_color(tex->ceiling);
		else if (scr_y < ray->wall_rng[1])
		{
			ray->tex_pos->y = (int) tex_h_unit % ray->tex_ptr->h;
			tex_h_unit += ray->tex_rate;
			tex_addr = ray->tex_ptr->addr;
			color = \
				tex_addr[ray->tex_ptr->h * ray->tex_pos->y + ray->tex_pos->x];\
			color = test(color, ray);
		}
		else
			color = get_color(tex->floor);
		*(scr->addr + scr_y * WIN_W + scr_x) = color;
		scr_y++;
	}
}

static void	set_tex_data(t_ray *ray, t_tex *texture)
{
	if (ray->hit_side == X && ray->ray_dir->x >= 0)
		ray->tex_ptr = texture->west;
	else if (ray->hit_side == X && ray->ray_dir->x < 0)
		ray->tex_ptr = texture->east;
	else if (ray->hit_side == Y && ray->ray_dir->y >= 0)
		ray->tex_ptr = texture->north;
	else if (ray->hit_side == Y && ray->ray_dir->y < 0)
		ray->tex_ptr = texture->south;
	ray->tex_pos->x = (int)(ray->wall_point * (double) ray->tex_ptr->w);
	if (ray->hit_side == X && ray->ray_dir->x < 0)
		ray->tex_pos->x = ray->tex_ptr->w - ray->tex_pos->x - 1;
	if (ray->hit_side == Y && ray->ray_dir->y > 0)
		ray->tex_pos->x = ray->tex_ptr->w - ray->tex_pos->x - 1;
	ray->tex_rate = (double) ray->tex_ptr->h / (double) ray->line_len;
}

static void	set_draw_data(t_ray *ray)
{
	ray->wall_rng[0] = (WIN_H - ray->line_len) / 2;
	if (ray->wall_rng[0] < 0)
		ray->wall_rng[0] = 0;
	ray->wall_rng[1] = (WIN_H + ray->line_len) / 2;
	if (ray->wall_rng[1] > WIN_H - 1)
		ray->wall_rng[1] = WIN_H - 1;
	if (ray->hit_side == X)
		ray->wall_point = \
			ray->pl_pos->y + ray->perp_wall_dist * ray->ray_dir->y;
	else
		ray->wall_point = \
			ray->pl_pos->x + ray->perp_wall_dist * ray->ray_dir->x;
	ray->wall_point -= floor(ray->wall_point);
}

void	draw(t_info *info, int scr_x)
{
	set_draw_data(info->ray);
	set_tex_data(info->ray, info->texture);
	set_scr_color(info->ray, info->texture, info->scr, scr_x);
}
