/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeunkim <hyeunkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 16:07:04 by hyeunkim          #+#    #+#             */
/*   Updated: 2024/06/20 18:53:21 by hyeunkim         ###   ########.fr       */
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

// map, posX, posY, dirX, dirY, moveSpeed, rotSpeed, planeX, planeY
typedef struct	s_data
{
	t_vec	*pos; // 플레이어 위치 벡터
	t_vec	*dir; //초기 플레이어의 단위 방향 벡터
	t_vec	*plane; //카메라 평면에 수평인 벡터 (dir와 plane은 수직)
	t_vec	*ray; // 광선의 방향 벡터 (단위)
	t_coor	*map;
	t_coor	*step;
	double	side_dist[2];
	double	delta_dist[2];
	double	perp_wall_dist;
	int		line_height;
	int		side;
}	t_data;

typedef struct	s_draw
{
	t_coor	texture;
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
	t_map	*map;
	t_tex	*texture;
	t_img	*screen;
	void    *mlx;
    void    *win;
	// 1) 변수가 따로 들어감
	// 2) 출력에 필요한 데이터가 포함된 구조체
	t_data	*calc;
}	t_info;

// checker.c
// static void	check_color(char *line, char type, int *elem_cnt);
// static void	check_texture(char *line, char type, int *elem_cnt);
// static void	check_scene(char *line, int *scene);
// static void	check_map_data(int fd, int *map_size);
void	check_format(char *file, int *map_size);

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

// util.c
int		get_rtrim_len(char *str, char *set);

//error.c
void	print_error(t_error flag, const char *func, int line);

//draw && calc
void	calc(t_info *info, t_data *calc, double cam_x);
void    draw(t_info *info, int screen_width);

// ray_loop.c
int		dev_close(int key, void *tmp);
int		key_press(int key, void *tmp);
void	raycasting_loop(t_info *info);
#endif