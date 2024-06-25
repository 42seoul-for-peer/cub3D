/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeunkim <hyeunkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 17:31:46 by hyeunkim          #+#    #+#             */
/*   Updated: 2024/06/24 22:13:22 by hyeunkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// void	print_error(t_error flag, const char *func, int line)
// {
// 	ft_printf("func %s[%d]\n", func, line);
// 	ft_putendl_fd("Error\n", STDERR_FILENO);
// 	ft_putstr_fd("cub3d: ", STDERR_FILENO);
// 	if (flag == sys_call)
// 		ft_putendl_fd(strerror(errno), STDERR_FILENO);
// 	else if (flag == map_data)
// 		ft_putendl_fd("invalid map data", STDERR_FILENO);
// 	else if (flag == map_file)
// 		ft_putendl_fd("invalid map file type", STDERR_FILENO);
// 	else if (flag == argument)
// 		ft_putendl_fd("\n\tusage: ./cub3d x.cub", STDERR_FILENO);
// 	else if (flag == lib_mlx)
// 		ft_putendl_fd("mlx error", STDERR_FILENO);
// 	else if (flag == tex)
// 		ft_putendl_fd("invalid texture path", STDERR_FILENO);
// 	exit(EXIT_FAILURE);
// }

void	exit_with_error(t_error flag)
{
	ft_putendl_fd("Error", STDERR_FILENO);
	ft_putstr_fd("cub3d: ", STDERR_FILENO);
	if (flag == sys_call)
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
	else if (flag == map_data)
		ft_putendl_fd("invalid map data", STDERR_FILENO);
	else if (flag == map_file)
		ft_putendl_fd("invalid map file", STDERR_FILENO);
	else if (flag == argument)
		ft_putendl_fd("\n\tusage: ./cub3d x.cub", STDERR_FILENO);
	else if (flag == lib_mlx)
		ft_putendl_fd("mlx error", STDERR_FILENO);
	else if (flag == tex)
		ft_putendl_fd("invalid texture path", STDERR_FILENO);
	exit(EXIT_FAILURE);
}

int	close_mlx(void)
{
	exit(EXIT_SUCCESS);
}
