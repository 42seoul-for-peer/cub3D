/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeunkim <hyeunkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 16:07:04 by hyeunkim          #+#    #+#             */
/*   Updated: 2024/06/13 16:17:22 by hyeunkim         ###   ########.fr       */
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
typedef enum e_type
{
	north = 0,
	south,
	west,
	east,
	floor_l,
	ceiling,
	scene
}	t_type;

typedef	enum e_error
{
	sys_call,
	map_data,
	map_file,
	argument
}	t_error;

/* ************************************************************************** */
typedef struct s_img
{
	void	*img;
	char	*addr;
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
}	t_texture;

typedef struct s_map
{
	char	*north;
	char	*south;
	char	*west;
	char	*east;
	int		*floor;
	int		*ceiling;
	int		*player_pos; //x, y, dir.
	int		width;
	int		height;
	char	**scene;
}	t_map;


typedef struct s_info
{
	t_map		*map;
	t_texture	*texture;
	t_img		*img;
	void    	*mlx;
    void    	*win;
	int			win_size[2];
}	t_info;

//init_info.c
t_info	*init_info(int fd);

//check_map.c
bool	check_map_format(t_map *map);

//get_map.c
t_map *get_map_format(t_map *map, int fd);

//parse_map.c
t_map *parse_map(int fd);

//error.c
void	print_error(t_error flag, const char *func);

//raycasting_tutorial.c
void	tutorial(t_info *info);

#endif