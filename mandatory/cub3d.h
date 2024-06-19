/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeunkim <hyeunkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 16:07:04 by hyeunkim          #+#    #+#             */
/*   Updated: 2024/06/19 16:29:09 by hyeunkim         ###   ########.fr       */
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

/* ************************************************************************** */
# define X 0
# define Y 1

# define WIN_WIDTH 1920
# define WIN_HEIGHT 1080

typedef	enum e_error
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
// bpp: bits per pixel 픽셀 하나를 표현하는 데 필요한 비트 수
// line: 이미지의 너비
typedef struct	s_texture
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


typedef struct s_info
{
	t_map	*map;
	t_tex	*texture;
	t_img	*screen;
	void    *mlx;
    void    *win;
}	t_info;

// checker.c
void	check_format(char *file, int *map_size);

//raycasting_tutorial.c
void	tutorial(t_info *info);

// init.c
// static void	init_mlx_data(t_info *info);
// static void	init_map_data(t_info *info, char *file, int *map_size);
t_info	*init_info(char *file, int *map_size);

// set_map_data.c
void	set_map_color(t_info *info, char *line, char type);
void	set_map_texture(t_info *info, char *str, char type);
void	set_map_scene(t_map *map, int fd);

// validate_scene.c
bool	is_surrounded(t_map *map, int x, int y);
bool	is_map_valid(t_map *map);


// util.c
int		get_rtrim_len(char *str, char *set);
bool	check_line(char *str);

//error.c
void	print_error(t_error flag, const char *func, int line);

#endif