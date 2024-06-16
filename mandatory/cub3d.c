/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeunkim <hyeunkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 16:07:15 by hyeunkim          #+#    #+#             */
/*   Updated: 2024/06/16 16:32:16 by hyeunkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	dev_print_info(t_info *info)
{
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
	t_info	*info;
	int		map_fd;

	if (argc != 2)
		print_error(argument, __func__);
	if (check_file_format(argv[1]) == false)
		print_error(map_file, __func__);
	map_fd = open(argv[1], O_RDONLY);
	if (map_fd < 0)
		print_error(sys_call, __func__);
	info = init_info(map_fd);
	dev_print_info(info);
	tutorial(info);
	free(info->map);
	exit(EXIT_SUCCESS);
}
