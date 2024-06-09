/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeunkim <hyeunkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 17:31:46 by hyeunkim          #+#    #+#             */
/*   Updated: 2024/06/09 20:09:40 by hyeunkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_error(t_error flag)
{
	ft_putstr_fd("cub3d: ", STDERR_FILENO);
	if (flag == syscall)
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
	else if (flag == map_data)
		ft_putendl_fd("invalid map data", STDERR_FILENO);
	else if (flag == argument)
		ft_putendl_fd("\n\tusage: ./cub3d x.cub", STDERR_FILENO);
	exit(EXIT_FAILURE);
}
