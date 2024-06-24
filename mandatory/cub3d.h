/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeunkim <hyeunkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 16:07:04 by hyeunkim          #+#    #+#             */
/*   Updated: 2024/06/24 15:11:06 by hyeunkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <mlx.h>
# include <fcntl.h>
# include <string.h>
# include <errno.h>
# include <stdbool.h>
# include <math.h>
# include "libft.h"
# include "key.h"
/* ************************************************************************** */
# define X 0
# define Y 1

# define WIN_WIDTH 1920
# define WIN_HEIGHT 1080
# define MOVE_SPEED 0.1
# define ROT_ANGLE 30
/* ************************************************************************** */
typedef enum e_error
{
	sys_call,
	map_data,
	map_file,
	argument,
	lib_mlx,
	tex
}	t_error;

/* ************************************************************************** */
typedef struct s_vector
{
	double	x;
	double	y;
}	t_vec;

typedef struct s_coordinate
{
	int	x;
	int	y;
}	t_coor;

typedef struct s_img
{
	void	*ptr;
	int		*addr;
	int		width;
	int		height;
	int		bpp;
	int		line;
	int		endian;
}	t_img;

typedef struct s_texture
{
	t_img	*north;
	t_img	*south;
	t_img	*west;
	t_img	*east;
	int		*floor;
	int		*ceiling;
}	t_tex;

typedef struct s_map
{
	int		width;
	int		height;
	char	**scene;
	t_coor	pos;
	char	player_dir;
}	t_map;

typedef struct s_data
{
	t_vec	*pos;
	t_vec	*dir;
	t_vec	*plane;
	t_vec	*ray;
	t_coor	*map;
	t_coor	*step;
	double	side[2];
	double	delta[2];
	double	perp_wall_dist;
	int		line_height;
	int		hit_side;
}	t_data;

typedef struct s_draw
{
	t_coor	texture;
	t_img	*img;
	double	ratio;
	double	tex_height_unit;
	double	wall_x;
	int		start_height;
	int		end_height;
	int		screen_width;
	int		side;
}	t_draw;

typedef struct s_info
{
	t_data	*calc;
	t_map	*map;
	t_tex	*texture;
	t_img	*screen;
	void	*mlx;
	void	*win;
}	t_info;

// checker.c
// static void	check_color(char *line, int *elem_cnt);
// static void	check_texture(char *line, int *elem_cnt);
// static void	check_scene(char *line, int *scene);
// static void	check_map_data(int fd, int *map_size);
int		*check_format(char *file);
// checker_util.c
void	check_color_value(char *line);
void	check_scene_line(char *line, int *player, int *map_size);

// init.c
// static void	init_mlx_data(t_info *info);
// static void	init_map_data(t_info *info, char *file, int *map_size);
t_info	*init_info(char *file, int *map_size);

// set_map_data.c
void	set_map_color(t_info *info, char *line, char type);
void	set_map_texture(t_info *info, char *str, char type);
void	set_map_scene(t_map *map, int fd);

// validate_scene.c
// static bool	is_surrounded(t_map *map, int x, int y);
bool	is_map_valid(t_map *map);

// ray_loop.c
void	raycasting_loop(t_info *info);

// calculator.c
// static void	set_dist(t_data *calc);
// static int	hit_loop(t_info *info, t_data *calc);
void	calculator(t_info *info, t_data *calc);

// draw.c
// static t_draw	get_draw_data(t_data *calc, int screen_width);
// static void		set_image_data(t_draw *draw, t_data *calc, t_tex *texture);
// static void		set_screen_color(t_info *info, t_draw draw);
// int				get_color_from_colorset(int *colorset);
void	draw(t_info *info, int screen_width);

// action.c
int		close_mlx(void);
int		key_press(int key, void *tmp);

// util.c
int		get_rtrim_len(char *str, char *set);

// error.c
void	print_error(t_error flag, const char *func, int line);

#endif