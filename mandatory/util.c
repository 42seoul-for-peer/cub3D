/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeunkim <hyeunkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 18:46:58 by hyeunkim          #+#    #+#             */
/*   Updated: 2024/06/23 14:55:00 by hyeunkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_rtrim_len(char *str, char *set)
{
	int	idx;
	int	len;

	if (!str)
		return (0);
	len = ft_strlen(str);
	idx = 0;
	while (idx < len && str[len - 1 - idx] \
			&& ft_strchr(set, str[len - 1 - idx]))
		idx++;
	return (len - idx);
}
