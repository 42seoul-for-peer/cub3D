/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeunkim <hyeunkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 16:07:04 by hyeunkim          #+#    #+#             */
/*   Updated: 2024/06/09 20:14:38 by hyeunkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <mlx.h>
# include <fcntl.h>
# include <string.h>
# include <errno.h>
# include "libft.h"

typedef	enum e_error
{
	sys_call,
	map_data,
	map_file,
	argument
}	t_error;

typedef struct s_mlx
{
    void    *mlx;
    void    *win;
}   t_mlx;

typedef struct s_map
{
	int		north;
	int		south;
	int		west;
	int		east;
	int		*floor;
	int		*ceiling;
	int		*player_pos; //x, y, dir.
	int		width;
	int		height;
	char	**scene;
}	t_map;

typedef enum e_type
{
	north = 0,
	south,
	west,
	east,
	floor,
	ceiling,
	scene
}	t_type;

//get_map.c
t_map *get_map_data(t_map *map, int fd);

//parse_map.c
t_map *parse_map(int fd);

//error.c
void	print_error(int flag);
#endif