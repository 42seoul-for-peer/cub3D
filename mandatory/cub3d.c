/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeunkim <hyeunkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 16:07:15 by hyeunkim          #+#    #+#             */
/*   Updated: 2024/06/24 22:09:20 by hyeunkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#define EVENT_DESTROY_NOTIFY 17

int	main(int argc, char *argv[])
{
	int		*map_size;
	t_info	*info;

	if (argc != 2)
		exit_with_error(argument);
	map_size = check_format(argv[1]);
	info = init_info(argv[1], map_size);
	raycasting_loop(info);
	mlx_hook(info->win, 2, 0, key_press, info);
	mlx_hook(info->win, EVENT_DESTROY_NOTIFY, 0, close_mlx, info);
	mlx_loop(info->mlx);
	exit(EXIT_SUCCESS);
}
