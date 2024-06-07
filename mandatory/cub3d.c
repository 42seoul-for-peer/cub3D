#include "cub3d.h"

int main(int argc, char *argv[])
{
	t_mlx	mlx;
	t_map	*map;
	int		map_fd;

	if (argc != 2)
    	error_with_str(ERR_ARG);
	map_fd = open(argv[1], O_RDONLY);
	if (map_fd < 0)
		error_with_str(ERR_SYSCALL);
	map = parse_map(map_fd);
  	mlx.mlx = mlx_init();
  	mlx.win = mlx_new_window(mlx.mlx, 960, 960, "test");
  	mlx_loop(mlx.mlx);
  	exit(EXIT_SUCCESS);
}