/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeunkim <hyeunkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 16:07:15 by hyeunkim          #+#    #+#             */
/*   Updated: 2024/06/17 15:17:49 by hyeunkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	dev_print_info(t_info *info, int *map_size)
{
	int idx= 0;
	ft_printf("map_size[Y] : %d\n", map_size[Y]);
	while (idx < map_size[Y])
		ft_printf("%s\n", info->map->scene[idx++]);
	ft_printf("Floor : (%d, %d, %d)\n", info->map->floor[0], info->map->floor[1], info->map->floor[2]);
	ft_printf("Ceiling : (%d, %d, %d)\n", info->map->ceiling[0], info->map->ceiling[1], info->map->ceiling[2]);
}

bool	check_file_format(char *path)
{
	char	*file_name;

	if (ft_strrchr(path, '/'))
		file_name = ft_strrchr(path, '/') + 1;
	else
		file_name = path;
	if (ft_strlen(file_name) < 5)
		return (false);
	if (ft_strchr(file_name, '.') != ft_strrchr(file_name, '.'))
		return (false);
	if (ft_strnstr(file_name, ".cub", ft_strlen(file_name)) == 0)
		return (false);
	if (ft_strncmp(ft_strnstr(file_name, ".cub", ft_strlen(file_name)), ".cub", 5))
		return (false);
	return (true);
}

int	main(int argc, char *argv[])
{
	int		*map_size;
	t_info	*info;

	// 1. 인자 개수 확인
	if (argc != 2)
		print_error(argument, __func__);
	map_size = NULL;
	map_size = check_format(argv[1]);
	// 2. map_size == NULL : 맵 파일 포맷 문제, map_size != NULL : 맵 파일 포맷 이상 없음
	// if (map_size == NULL)
	// 	print_error(map_file, __func__);
	info = get_format(argv[1], map_size);
	// 3. info == NULL : get_format 중 문제 발생(calloc?)
	if (info == 0)
		print_error(map_file, __func__);
	// 3-1. dev_print
	dev_print_info(info, map_size);
	// 4. raycasting 시작
	tutorial(info);
	// 5. info, map_size 메모리 해제
	free(map_size);
	free(info->map);	// need to change;
	exit(EXIT_SUCCESS);
}
