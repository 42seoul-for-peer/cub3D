/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeunkim <hyeunkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 17:31:46 by hyeunkim          #+#    #+#             */
/*   Updated: 2024/06/17 13:28:04 by hyeunkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_error(t_error flag, const char *func)
{
	ft_printf("func %s\n", func);
	ft_putstr_fd("cub3d: ", STDERR_FILENO);
	if (flag == sys_call)
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
	else if (flag == map_data)
		ft_putendl_fd("invalid map data", STDERR_FILENO);
	else if (flag == map_file)
		ft_putendl_fd("invalid map file type", STDERR_FILENO);
	else if (flag == argument)
		ft_putendl_fd("\n\tusage: ./cub3d x.cub", STDERR_FILENO);
	else if (flag == lib_mlx)
		ft_putendl_fd("mlx error", STDERR_FILENO);
	else if (flag == tex)
		ft_putendl_fd("invalid texture path", STDERR_FILENO);
	exit(EXIT_FAILURE);
}
