/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isspace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeunkim <hyeunkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 17:23:21 by hyeunkim          #+#    #+#             */
/*   Updated: 2024/06/16 17:26:12 by hyeunkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isspace(int val)
{
	if (8 < val && val < 14)
		return (1);
	else if (val == 32)
		return (1);
	return (0);
}