#ifndef CUB3D_H
# define CUB3D_H

# include <mlx.h>
# include <fcntl.h>
# include <string.h>
# include <errno.h>
# include "libft.h"

# define ERR_SYSCALL 1
# define ERR_MAP 2
# define ERR_ARG 3

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
	int		floor[3];
	int		ceiling[3];
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
void	error_with_str(int flag);
#endif