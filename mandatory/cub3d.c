/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeunkim <hyeunkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 16:07:15 by hyeunkim          #+#    #+#             */
/*   Updated: 2024/06/23 15:36:07 by hyeunkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#define EVENT_DESTROY_NOTIFY 17

void	check_leak(void)
{
	system("leaks cub3D");
}

int	close_mlx(void)
{
	exit(EXIT_SUCCESS);
}

	// atexit(check_leak);
int	main(int argc, char *argv[])
{
	int		map_size[2];
	t_info	*info;

	if (argc != 2)
		print_error(argument, __func__, __LINE__);
	check_format(argv[1], map_size);
	info = init_info(argv[1], map_size);
	raycasting_loop(info);
	mlx_hook(info->win, 2, 0, key_press, info);
	mlx_hook(info->win, EVENT_DESTROY_NOTIFY, 0, close_mlx, info);
	mlx_loop(info->mlx);
	free(info->map);
	exit(EXIT_SUCCESS);
}
