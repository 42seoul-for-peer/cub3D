/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeunkim <hyeunkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 16:07:15 by hyeunkim          #+#    #+#             */
/*   Updated: 2024/06/19 17:36:19 by hyeunkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char *argv[])
{
	int		map_size[2];
	t_info	*info;

	// 1. 맵 파일 인자, 파일 내부 포맷 확인
	if (argc != 2)
		print_error(argument, __func__, __LINE__);
	check_format(argv[1], map_size);
	// 2. info 초기화
	info = init_info(argv[1], map_size);
	// 3. raycasting 시작
	tutorial(info);
	free(info->map);
	exit(EXIT_SUCCESS);
}
