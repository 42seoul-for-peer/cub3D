/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeunkim <hyeunkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 14:44:59 by hyeunkim          #+#    #+#             */
/*   Updated: 2024/06/24 15:25:31 by hyeunkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_color_value(char *line)
{
	int	comma_cnt;
	int	color_cnt;

	comma_cnt = 0;
	color_cnt = 0;
	while (line && *line)
	{
		if (ft_isdigit(*line))
		{
			color_cnt += 1;
			if (ft_atoi(line) < 0 || ft_atoi(line) > 255)
				print_error(map_data, __func__, __LINE__);
			while (ft_isdigit(*line))
				line++;
		}
		if (*line == ',')
			comma_cnt += 1;
		line++;
	}
	if (comma_cnt != 2 || color_cnt != 3)
		print_error(map_data, __func__, __LINE__);
}

void	check_scene_line(char *line, int *player, int *map_size)
{
	static int	flag;

	if (ft_strchr(line, '1'))
	{
		if (flag == 0)
			flag = 1;
		else if (flag == 2)
			print_error(map_data, __func__, __LINE__);
		map_size[1] += 1;
		if (get_rtrim_len(line, " \n") > map_size[1])
			map_size[0] = get_rtrim_len(line, " \n");
		if (ft_strchr(line, 'N') || ft_strchr(line, 'S') || \
			ft_strchr(line, 'W') || ft_strchr(line, 'E'))
			*player += 1;
	}
	else if (flag == 1)
		flag = 2;
	if (flag != 1 && get_rtrim_len(line, " \n") != 0)
		print_error(map_data, __func__, __LINE__);
	while (*line)
	{
		if (!ft_strchr("NSWE10 \n", *line))
			print_error(map_data, __func__, __LINE__);
		line++;
	}
}
