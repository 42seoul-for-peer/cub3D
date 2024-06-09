/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeunkim <hyeunkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 16:07:15 by hyeunkim          #+#    #+#             */
/*   Updated: 2024/06/09 16:15:58 by hyeunkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void dev_print_mapFormat(t_map *map) //map 출력
{
	int idx = 0;
	ft_printf("north : %d\n", map->north);
	ft_printf("south : %d\n", map->south);
	ft_printf("west : %d\n", map->west);
	ft_printf("east : %d\n", map->east);
	ft_printf("floor : %d %d %d\n", map->floor[0], map->floor[1], map->floor[2]);
	ft_printf("ceiling : %d %d %d\n", map->ceiling[0], map->ceiling[1], map->ceiling[2]);
	ft_printf("map format : \n");
	while (map->scene[idx] != 0)
	{
		ft_printf("%s\n", map->scene[idx]);
		idx++;
	}
}

int dev_close(int key, void *test) //mlx key hook (ESC)
{
	test = 0;
	if (key == 53)
		exit(0);
	return (0);
}

int main(int argc, char *argv[])
{
	t_mlx	mlx;
	t_map	*map;
	int		map_fd;

	if (argc != 2)
    	print_error(ERR_ARG);
	map_fd = open(argv[1], O_RDONLY);
	if (map_fd < 0)
		print_error(ERR_SYSCALL);
	map = parse_map(map_fd);
	dev_print_mapFormat(map);
  	mlx.mlx = mlx_init();
  	mlx.win = mlx_new_window(mlx.mlx, 960, 960, "test");
	// mlx_hook(mlx.win, 2, 0, &dev_close, 0);
  	// mlx_loop(mlx.mlx);
	free(map); // leak을 의심하자
  	exit(EXIT_SUCCESS);
}