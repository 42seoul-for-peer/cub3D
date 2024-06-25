/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeunkim <hyeunkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 14:44:59 by hyeunkim          #+#    #+#             */
/*   Updated: 2024/06/25 13:17:26 by hyeunkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_color_value(char *line)
{
	int	flag;
	int	cnt[2];

	ft_memset(cnt, 0, sizeof(int) * 2);
	flag = 0;
	while (line && *line)
	{
		if (flag == 0 && ft_isdigit(*line))
		{
			flag = 1;
			cnt[0] += 1;
			if (ft_atoi(line) < 0 || ft_atoi(line) > 255)
				exit_with_error(map_data);
			while (ft_isdigit(*line))
				line++;
		}
		if (flag == 1 && *line == ',')
		{
			flag = 0;
			cnt[1] += 1;
		}
		line++;
	}
	if (cnt[0] != 3 || cnt[1] != 2)
		exit_with_error(map_data);
}

void	check_scene_line(char *line, int *player, int *map_size)
{
	static int	flag;

	if (ft_strchr(line, '1'))
	{
		if (flag == 0)
			flag = 1;
		else if (flag == 2)
			exit_with_error(map_data);
		map_size[1] += 1;
		if (get_rtrim_len(line, " \n") > map_size[0])
			map_size[0] = get_rtrim_len(line, " \n");
		if (ft_strchr(line, 'N') || ft_strchr(line, 'S') || \
			ft_strchr(line, 'W') || ft_strchr(line, 'E'))
			*player += 1;
	}
	else if (flag == 1)
		flag = 2;
	if (flag != 1 && get_rtrim_len(line, " \n") != 0)
		exit_with_error(map_data);
	while (*line)
	{
		if (!ft_strchr("NSWE10 \n", *line))
			exit_with_error(map_data);
		line++;
	}
}
