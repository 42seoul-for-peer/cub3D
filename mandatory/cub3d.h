/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeunkim <hyeunkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 16:07:04 by hyeunkim          #+#    #+#             */
/*   Updated: 2024/06/17 15:59:18 by hyeunkim         ###   ########.fr       */
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

typedef enum e_type
{
	error = -1,
	north,
	south,
	west,
	east,
	floor_color,
	ceiling_color,
	scene
}	t_type;

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

typedef struct s_coodinate
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
}	t_tex;

typedef struct s_map
{
	char	*north;
	char	*south;
	char	*west;
	char	*east;
	int		*floor;
	int		*ceiling;
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

//init_info.c
t_info	*init_info(int fd);

// //check_map.c
// bool	check_map_format(t_map *map);

// checker.c
void	check_format(char *file, int *map_size);

//error.c
void	print_error(t_error flag, const char *func, int line);

//raycasting_tutorial.c
void	tutorial(t_info *info);

// get_format.c
t_info	*get_format(char *file, int *map_size);

// get_format_map.c
void    get_map(t_map *map, int fd, int *map_size);
#endif