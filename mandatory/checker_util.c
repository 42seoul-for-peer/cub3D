/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeunkim <hyeunkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 14:44:59 by hyeunkim          #+#    #+#             */
/*   Updated: 2024/06/25 15:03:58 by hyeunkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_color_value(char *line)
{
	int		cnt;
	char	*tmp;

	if (!line)
		exit_with_error(sys_call);
	cnt = 0;
	tmp = line;
	while (*tmp && cnt < 3)
	{
		while (ft_isspace(*tmp))
			tmp++;
		if (!ft_isdigit(*tmp) || ft_atoi(tmp) < 0 || ft_atoi(tmp) > 255)
			exit_with_error(map_data);
		while (ft_isdigit(*tmp))
			tmp++;
		while (ft_isspace(*tmp))
			tmp++;
		if (cnt < 2 && *tmp == ',')
			tmp++;
		cnt++;
	}
	if (cnt != 3 || *tmp)
		exit_with_error(map_data);
	free(line);
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
