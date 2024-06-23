/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeunkim <hyeunkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 16:07:15 by hyeunkim          #+#    #+#             */
/*   Updated: 2024/06/22 14:25:56 by hyeunkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_leak(void)
{
	system("leaks cub3D");
}

int	main(int argc, char *argv[])
{
	int		map_size[2];
	t_info	*info;

	atexit(check_leak);
	if (argc != 2)
		print_error(argument, __func__, __LINE__);
	check_format(argv[1], map_size);
	info = init_info(argv[1], map_size);
	raycasting_loop(info);
	mlx_hook(info->win, 17, 0, dev_close, 0);
	mlx_hook(info->win, 2, 0, key_press, info);
    mlx_loop(info->mlx);
	free(info->map);
	exit(EXIT_SUCCESS);
}
